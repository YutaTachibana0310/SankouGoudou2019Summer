//=============================================================================
//
// プレイヤーコントローラー処理 [PlayerController.cpp]
// Author : 渡邉良則
//
//=============================================================================
#include "main.h"
#include "player.h"
#include "star.h"
#include "PlayerController.h"
#include "InputController.h"
#include "debugWindow.h"
#include "IStateMachine.h"
#include <map>
#include "PlayerMove.h"
#include "PlayerReturn.h"
#include "PlayerWait.h"

using namespace std;

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MOVETARGET_LENGTH				(6)
#define PLAYER_DISTANCE_FROM_CAMERA		(1500.0f)

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
	/*MovePos[TOP] = PLAYER_TOP;
	MovePos[MIDDLE_LEFT] = PLAYER_MIDDLE_LEFT;
	MovePos[LOWER_LEFT] = PLAYER_LOWER_LEFT;
	MovePos[LOWER_RIGHT] = PLAYER_LOWER_RIGHT;
	MovePos[MIDDLE_RIGHT] = PLAYER_MIDDLE_RIGHT;
	MovePos[CENTER] = PLAYER_CENTER;*/
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
	player.CurrentState = PlayerState::Wait;

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

	player.Update();
	fsm[player.CurrentState]->OnUpdate(&player);
}

//*****************************************************************************
// 描画処理
//*****************************************************************************
void DrawPlayerController()
{
	player.Draw();

}

//*****************************************************************************
// 入力確認
//*****************************************************************************
void CheckInput(HWND hWnd)
{
	//Wait状態以外は入力を受け付けない
	if (player.CurrentState != PlayerState::Wait)
		return;

	//各ボタンについて確認
	for (int i = 0; i < STAR_MAX; i++)
	{
		if (!IsEntered(i, hWnd))
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
// Player状態遷移処理
//=============================================================================
void ChangeState(Player *player, PlayerState next)
{
	fsm[player->CurrentState]->OnExit(player);
	player->CurrentState = next;
	fsm[player->CurrentState]->OnStart(player);
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
