//=============================================================================
//
// プレイヤーコントローラー処理 [PlayerController.cpp]
// Author : 渡邉良則
//
//=============================================================================
#include "main.h"
#include "player.h"
#include "starUI.h"
#include "PlayerController.h"
#include "InputController.h"
#include "debugWindow.h"
#include "IStateMachine.h"
#include <map>
#include "PlayerMove.h"
#include "PlayerReturn.h"
#include "PlayerWait.h"
#include "PlayerBullet.h"
#include <vector>
#include "GameParticleManager.h"

using namespace std;

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MOVETARGET_LENGTH				(6)
#define PLAYER_DISTANCE_FROM_CAMERA		(150.0f)

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void push(void);				//移動履歴スタックへのプッシュ処理
void CheckInput(HWND hWnd);		//入力判定
void CheckComboReset(void);		//リセット確認
void CalcPlayerMoveTargetPos();	//移動目標座標計算処理

//*****************************************************************************
// グローバル変数
//*****************************************************************************

//一定時間入力がない場合に初期ポジションに戻る為のタイマー
int resetcount;

//判定用の配列
int judgment[JUDG_LEN] = { TOP,LOWER_LEFT,MIDDLE_RIGHT,MIDDLE_LEFT,LOWER_RIGHT };

//判定用配列の現在位置
int judg_currentCCW;
int judg_currentCW;

//現在の位置
int currentCCW;
int currentCW;

//移動先の番号保管配列
int move_stackCCW[MOVESTACK_LENGTH];
int move_stackCW[MOVESTACK_LENGTH];

// 何番に移動するかを保管
int	movenum;

//判定配列の内容と合っているかの判定
bool matchingCCW;
bool matchingCW;

//ボム発生テスト用フラグ
bool flag;
int flagtimer;

//プレイヤーステートマシン
static map<PlayerState, IStateMachine<Player>*> fsm;

//プレイヤー
Player player;

//移動先座標
D3DXVECTOR3 MovePos[MOVETARGET_LENGTH];

//バレットコンテナ
vector<PlayerBullet*> bulletContainer;

//*****************************************************************************
// 初期化処理
//*****************************************************************************
HRESULT InitPlayerController(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//ステートマシン初期化
	fsm[PlayerState::Move] = new PlayerMove();
	fsm[PlayerState::Wait] = new PlayerWait();
	fsm[PlayerState::Return] = new PlayerReturn();

	//プレイヤー初期化
	player.Init();

	//移動履歴スタックを初期化
	for (int i = 0; i < MOVESTACK_LENGTH; i++) {
		move_stackCCW[i] = INITIAL_ARRAY_NUMBER;
		move_stackCW[i] = INITIAL_ARRAY_NUMBER;
	}

	//移動目標初期化
	MovePos[CENTER] = PLAYER_CENTER;
	CalcPlayerMoveTargetPos();

	//一筆書き判定用変数を初期化
	currentCCW = 0;
	currentCW = 0;

	judg_currentCCW = 0;
	judg_currentCW = 0;
	matchingCCW = false;
	matchingCW = false;

	movenum = CENTER;

	resetcount = 0;

	flag = false;
	flagtimer = 0;

	//プレイヤーをWait状態に遷移
	player.currentState = PlayerState::Wait;
	player.active = true;

	//PlayerTrailParticleをセット
	SetPlayerTrailParticle(&player.pos, &player.active);

	return S_OK;
}
//*****************************************************************************
// 終了処理
//*****************************************************************************
void UninitPlayerController()
{
	fsm.clear();
	player.Uninit();
}

//*****************************************************************************
// 更新処理
//*****************************************************************************
void UpdatePlayerController(HWND hWnd)
{
	BeginDebugWindow("PlayerController");
	if (DebugButton("BUllet"))
	{
		int start = RandomRange(0, 5);
		int end = WrapAround(0, 5, start + RandomRange(1, 4));
		FirePlayerBullet((TrailIndex)start, (TrailIndex)end);
	}
	DebugText("PlayerBulletCnt : %d", bulletContainer.size());
	DebugText("PlayerState:%d", (int)player.currentState);
	EndDebugWindow("PlayerController");

	resetcount++;

	//ボム発生用のフラグ、カウンタ
	if (flag == true) {
		flagtimer++;
		if (flagtimer > RESETTIME) {
			flag = false;
			flagtimer = 0;
		}
	}

	//移動の入力確認
	CheckInput(hWnd);

	//コンボリセット確認
	CheckComboReset();

	//プレイヤーをアップデート
	player.Update();
	fsm[player.currentState]->OnUpdate(&player);

	//プレイヤーバレットをアップデート
	for (auto itr = bulletContainer.begin(); itr != bulletContainer.end(); itr++)
	{
		(*itr)->Update();
	}
}

//*****************************************************************************
// 描画処理
//*****************************************************************************
void DrawPlayerController()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//プレイヤー描画
	player.Draw();
}

//*****************************************************************************
//　プレイヤーバレット描画処理
//*****************************************************************************
void DrawPlayerBullet()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	pDevice->SetRenderState(D3DRS_LIGHTING, false);
	//pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, false);

	//プレイヤーバレット描画
	for (auto itr = bulletContainer.begin(); itr != bulletContainer.end(); itr++)
	{
		(*itr)->Draw();
	}

	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	pDevice->SetRenderState(D3DRS_LIGHTING, true);
	//pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, false);
}

//*****************************************************************************
// 入力確認
//*****************************************************************************
void CheckInput(HWND hWnd)
{
	//Wait状態以外は入力を受け付けない
	if (player.currentState != PlayerState::Wait)
		return;

	//各ボタンについて確認
	for (int i = 0; i < STAR_MAX; i++)
	{
		if (!IsEntered(i))
			continue;

		movenum = i;
		push();
		player.goalpos = MovePos[i];
		ChangeState(&player, PlayerState::Move);

		CheckCW();
		CheckCCW();
		resetcount = 0;
	}
}

//*****************************************************************************
// リセット確認
//*****************************************************************************
void CheckComboReset(void)
{
	//時間経過していなければ何もしない
	if (resetcount < RESETTIME)
		return;

	
	//中央へ戻る
	movenum = 5;
	push();
	ChangeState(&player, PlayerState::Return);

	CheckCW();
	CheckCCW();
	resetcount = 0;

}

//*****************************************************************************
// 判定用スタックへの移動履歴プッシュ処理
//*****************************************************************************
void push()
{
	//移動保管配列に入力されたキーの番号を保管
	if (currentCCW < MOVESTACK_LENGTH) {
		move_stackCCW[currentCCW] = movenum;
		move_stackCW[currentCW] = movenum;
	}
}

//*****************************************************************************
// ☆型一筆書き判定（右回り）
//*****************************************************************************
void CheckCW()
{
	//初回に判定用配列の何番目に同じ数字が格納されているか確認
	if (matchingCW == false) {
		for (judg_currentCW = 0; judg_currentCW < JUDG_LEN; judg_currentCW++) {

			//一致した場合
			if (move_stackCW[currentCW] == judgment[judg_currentCW]) {

				matchingCW = true;

			}
			if (matchingCW == true) {
				//移動保管配列と判定用配列が一致した場合抜ける（judgment_currentの値を確保）
				break;
			}
		}
	}

	//判定用配列の最大値まで進んだ場合、最初に戻す
	if (judg_currentCW < 0) {
		judg_currentCW = JUDG_LEN - 1;
	}

	//移動保管配列と判定用配列と違う場合（右回り）
	if (move_stackCW[currentCW] != judgment[judg_currentCW])
	{

		matchingCW = false;
		currentCW = 0;
		//移動保管配列を初期化
		for (int i = 0; i < MOVESTACK_LENGTH; i++) {
			move_stackCW[i] = INITIAL_ARRAY_NUMBER;
		}
	}
	else
	{
		//正しい場合
		matchingCW = true;
		judg_currentCW--;
		currentCW++;

		//移動保管配列の最大値まで達した場合ボム発生処理
		if (matchingCW == true && currentCW == MOVESTACK_LENGTH) {
			currentCW = 0;
			judg_currentCW = 0;
			matchingCW = false;
			flag = true;

			//配列の初期化
			for (int i = 0; i < MOVESTACK_LENGTH; i++) {
				move_stackCW[i] = INITIAL_ARRAY_NUMBER;
			}

			move_stackCW[currentCW] = movenum;
			currentCW++;
		}
	}
}

//*****************************************************************************
// ☆型一筆書き判定（左回り）
//*****************************************************************************
void CheckCCW() {

	//初回に判定用配列の何番目に同じ数字が格納されているか確認
	if (matchingCCW == false) {
		for (judg_currentCCW = 0; judg_currentCCW < JUDG_LEN; judg_currentCCW++) {

			//一致した場合
			if (move_stackCCW[currentCCW] == judgment[judg_currentCCW]) {
				matchingCCW = true;
			}
			if (matchingCCW == true) {
				//移動保管配列と判定用配列が一致した場合抜ける（judgment_currentの値を確保）
				break;
			}

		}
	}

	//判定用配列の最大値まで進んだ場合、最初に戻す
	if (judg_currentCCW >= JUDG_LEN) {
		judg_currentCCW = 0;
	}

	//移動保管配列と判定用配列と違う場合（左回り）
	if (move_stackCCW[currentCCW] != judgment[judg_currentCCW]) {

		matchingCCW = false;
		currentCCW = 0;
		//移動保管配列を初期化
		for (int i = 0; i < MOVESTACK_LENGTH; i++) {
			move_stackCCW[i] = INITIAL_ARRAY_NUMBER;
		}

	}
	else {
		//正しい場合
		matchingCCW = true;
		judg_currentCCW++;
		currentCCW++;

		//移動保管配列の最大値まで達した場合ボム発生処理
		if (matchingCCW == true && currentCCW == MOVESTACK_LENGTH) {
			currentCCW = 0;
			judg_currentCCW = 0;
			matchingCCW = false;
			flag = true;

			//配列の初期化
			for (int i = 0; i < MOVESTACK_LENGTH; i++) {
				move_stackCCW[i] = INITIAL_ARRAY_NUMBER;
			}

			move_stackCCW[currentCCW] = movenum;
			currentCCW++;
		}
	}

}

bool SetBomb() {
	if (flag == true) {
		return true;
	}
	return false;
}

//=============================================================================
// プレイヤーバレットコンテナ取得処理
//=============================================================================
vector<PlayerBullet*>* GetPlayerBulletContainer(void)
{
	return &bulletContainer;
}

//=============================================================================
// Player状態遷移処理
//=============================================================================
void ChangeState(Player *player, PlayerState next)
{
	fsm[player->currentState]->OnExit(player);
	player->currentState = next;
	fsm[player->currentState]->OnStart(player);
}

//=============================================================================
// 移動目標座標計算処理
//=============================================================================
void CalcPlayerMoveTargetPos()
{
	//スターのスクリーン座標を取得
	D3DXVECTOR3 starPos[5];
	GetStarPosition(starPos);

	for (int i = 0; i < STAR_MAX; i++)
	{
		//スターの位置でNear面とFar面を結ぶレイを計算して正規化
		D3DXVECTOR3 nearPos, farPos;
		CalcScreenToWorld(&nearPos, &starPos[i], 0.0f);
		CalcScreenToWorld(&farPos, &starPos[i], 1.0f);

		D3DXVECTOR3 ray = farPos - nearPos;
		D3DXVec3Normalize(&ray, &ray);

		//目標座標を計算
		MovePos[i] = nearPos + ray * PLAYER_DISTANCE_FROM_CAMERA;
	}
}

//=============================================================================
//　プレイヤーバレット発射処理
//=============================================================================
void FirePlayerBullet(TrailIndex start, TrailIndex end)
{
	for (auto itr = bulletContainer.begin(); itr != bulletContainer.end(); itr++)
	{
		if ((*itr)->IsActive())
			continue;
		
		//セットしてリターン
		(*itr)->SetTrailIndex(start, end);
		(*itr)->SetEdgePos(&MovePos[(int)start], &MovePos[(int)end]);
		(*itr)->Init();
		return;

	}

	//新しく生成して追加
	PlayerBullet *bullet = new PlayerBullet();
	bullet->SetTrailIndex(start, end);
	bullet->SetEdgePos(&MovePos[(int)start], &MovePos[(int)end]);
	bullet->Init();
	bulletContainer.push_back(bullet);
	return;
}

//=============================================================================
//　プレイヤーバレット発射処理
//=============================================================================
void FirePlayerBullet(D3DXVECTOR3 *rightPos, D3DXVECTOR3 *leftPos)
{
	int start = 0, end = 0;
	for (int i = 0; i < STAR_MAX; i++)
	{
		if (MovePos[i] == *rightPos)
			start = i;

		if (MovePos[i] == *leftPos)
			end = i;
	}

	for (auto itr = bulletContainer.begin(); itr != bulletContainer.end(); itr++)
	{
		if ((*itr)->IsActive())
			continue;

		//セットしてリターン
		(*itr)->SetTrailIndex((TrailIndex)start, (TrailIndex)end);
		(*itr)->SetEdgePos(&MovePos[(int)start], &MovePos[(int)end]);
		(*itr)->Init();
		return;

	}

	//新しく生成して追加
	PlayerBullet *bullet = new PlayerBullet();
	bullet->SetTrailIndex((TrailIndex)start, (TrailIndex)end);
	bullet->SetEdgePos(&MovePos[(int)start], &MovePos[(int)end]);
	bullet->Init();
	bulletContainer.push_back(bullet);
	return;
}

//=============================================================================
// CCW配列取得処理 (おーはま追記)
//=============================================================================
void GetMove_StackCCW(int trailHistoryCCW[MOVESTACK_LENGTH]) {
	for (int i = 0; i < MOVESTACK_LENGTH; i++) {
		trailHistoryCCW[i] = move_stackCCW[i];
	}
}

//=============================================================================
// CW配列取得処理 (おーはま追記)
//=============================================================================
void GetMove_StackCW(int trailHistoryCW[MOVESTACK_LENGTH]) {
	for (int i = 0; i < MOVESTACK_LENGTH; i++) {
		trailHistoryCW[i] = move_stackCW[i];
	}
}
