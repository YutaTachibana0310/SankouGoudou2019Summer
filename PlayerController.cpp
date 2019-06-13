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

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void push(void);

using namespace std;

static map<PlayerState, IStateMachine<Player>*> fsm;

Player player;

D3DXVECTOR3 MovePos[MAX_LENGTH];

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
int move_stackCCW[MAX_LENGTH];
int move_stackCW[MAX_LENGTH];

// 何番に移動するかを保管
int	movenum;

//判定配列の内容と合っているかの判定
bool matchingCCW;
bool matchingCW;

//ボム発生テスト用フラグ
bool flag;
int flagtimer;
//*****************************************************************************
// 初期化処理
//*****************************************************************************
HRESULT InitPlayerController(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	fsm[PlayerState::Move] = new PlayerMove();
	fsm[PlayerState::Wait] = new PlayerWait();
	fsm[PlayerState::Return] = new PlayerReturn();

	player.Init();
	for (int i = 0; i < MAX_LENGTH; i++) {
		move_stackCCW[i] = 0;
		move_stackCW[i] = 0;
	}

	MovePos[CENTER] = PLAYER_CENTER;
	MovePos[TOP] = PLAYER_TOP;
	MovePos[MIDDLE_LEFT] = PLAYER_MIDDLE_LEFT;
	MovePos[LOWER_LEFT] = PLAYER_LOWER_LEFT;
	MovePos[LOWER_RIGHT] = PLAYER_LOWER_RIGHT;
	MovePos[MIDDLE_RIGHT] = PLAYER_MIDDLE_RIGHT;

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
	if (player.CurrentState == PlayerState::Wait)
	{
		for (int i = 0; i < STAR_MAX; i++) {
			if (IsEntered(i, hWnd)) {
				movenum = i;
				push();
				player.goalpos = MovePos[i];
				ChangeState(&player, PlayerState::Move);

				CheckCW();
				CheckCCW();
				resetcount = 0;

			}
		}
	}
	//一定時間後に中央へ戻る処理
	if (resetcount >= RESETTIME) {
		movenum = 5;
		push();
		CheckCW();
		CheckCCW();
		resetcount = 0;
	}
	DebugText("move_stackCCW:%d,%d,%d,%d,%d,%d\n", move_stackCCW[0], move_stackCCW[1], move_stackCCW[2], move_stackCCW[3], move_stackCCW[4], move_stackCCW[5]);
	DebugText("move_stackCW:%d,%d,%d,%d,%d,%d\n", move_stackCW[0], move_stackCW[1], move_stackCW[2], move_stackCW[3], move_stackCW[4], move_stackCW[5]);
	
	
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
// 検証用
//*****************************************************************************

void SetPlayerTargetPosition(int *n) {

	*n = movenum;

}

void push() {

	//移動保管配列に入力されたキーの番号を保管
	if (currentCCW < MAX_LENGTH) {
		move_stackCCW[currentCCW] = movenum;
		move_stackCW[currentCW] = movenum;

	}

}

//右回り用
void CheckCW() {

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
	if (move_stackCW[currentCW] != judgment[judg_currentCW]) {

		matchingCW = false;
		currentCW = 0;
		//移動保管配列を初期化
		for (int i = 0; i < MAX_LENGTH; i++) {
			move_stackCW[i] = 0;
		}
	}
	else {
		//正しい場合
		matchingCW = true;
		judg_currentCW--;
		currentCW++;

		//移動保管配列の最大値まで達した場合ボム発生処理
		if (matchingCW == true && currentCW == MAX_LENGTH) {
			currentCW = 0;
			judg_currentCW = 0;
			matchingCW = false;
			flag = true;

			//配列の初期化
			for (int i = 0; i < MAX_LENGTH; i++) {
				move_stackCW[i] = 0;
			}

			move_stackCW[currentCW] = movenum;
			currentCW++;
		}

	}
}

//左回り用
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
		for (int i = 0; i < MAX_LENGTH; i++) {
			move_stackCCW[i] = 0;
		}

	}
	else {
		//正しい場合
		matchingCCW = true;
		judg_currentCCW++;
		currentCCW++;

		//移動保管配列の最大値まで達した場合ボム発生処理
		if (matchingCCW == true && currentCCW == MAX_LENGTH) {
			currentCCW = 0;
			judg_currentCCW = 0;
			matchingCCW = false;
			flag = true;

			//配列の初期化
			for (int i = 0; i < MAX_LENGTH; i++) {
				move_stackCCW[i] = 0;
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

void ChangeState(Player *player,PlayerState next)
{
	fsm[player->CurrentState]->OnExit(player);
	player->CurrentState = next;
	fsm[player->CurrentState]->OnStart(player);
}