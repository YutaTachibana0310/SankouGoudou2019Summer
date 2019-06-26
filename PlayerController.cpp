//=============================================================================
//
// プレイヤーコントローラー処理 [PlayerController.cpp]
// Author : 渡邉良則
//
//=============================================================================
#include "main.h"
#include "starUI.h"
#include "PlayerController.h"
#include "InputController.h"
#include "debugWindow.h"
#include "GameParticleManager.h"
#include "PlayerObserver.h"

using namespace std;

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MOVETARGET_LENGTH				(6)
#define PLAYER_DISTANCE_FROM_CAMERA		(150.0f)

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void CalcPlayerMoveTargetPos();
void CheckInput(HWND hWnd);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
PlayerObserver *observer;

//*****************************************************************************
// 初期化処理
//*****************************************************************************
HRESULT InitPlayerController(void)
{
	observer = new PlayerObserver();
	observer->Init();

	//移動目標初期化
	CalcPlayerMoveTargetPos();

	return S_OK;
}
//*****************************************************************************
// 終了処理
//*****************************************************************************
void UninitPlayerController()
{
	observer->Uninit();
	delete observer;
}

//*****************************************************************************
// 更新処理
//*****************************************************************************
void UpdatePlayerController(HWND hWnd)
{
	//移動の入力確認
	CheckInput(hWnd);

	observer->Update();
}

//*****************************************************************************
// 描画処理
//*****************************************************************************
void DrawPlayerController()
{
	observer->Draw();
}

//*****************************************************************************
// 入力確認
//*****************************************************************************
void CheckInput(HWND hWnd)
{
	//各ボタンについて確認
	for (int i = 0; i < STAR_MAX; i++)
	{
		if (!IsEntered(i))
			continue;

		observer->PushInput(i);
		return;
	}
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
		D3DXVECTOR3 pos = nearPos + ray * PLAYER_DISTANCE_FROM_CAMERA;
		observer->SetMoveTargetPosition(i, pos);
	}
}

//リファクタリングしたのでエラー対策に仮版
bool SetBomb()
{
	return true;
}

//=============================================================================
// CCW配列取得処理 (おーはま追記)
// 追記（立花）：リファクタリングでデータ構造が変わったので要相談
//=============================================================================
void GetMove_StackCCW(int trailHistoryCCW[MOVESTACK_LENGTH]) {

	for (int i = 0; i < MOVESTACK_LENGTH; i++) {
		trailHistoryCCW[i] = INITIAL_ARRAY_NUMBER;
	}
}

//=============================================================================
// CW配列取得処理 (おーはま追記)
// 追記（立花）：リファクタリングでデータ構造が変わったので要相談
//=============================================================================
void GetMove_StackCW(int trailHistoryCW[MOVESTACK_LENGTH]) {
	for (int i = 0; i < MOVESTACK_LENGTH; i++) {
		trailHistoryCW[i] = INITIAL_ARRAY_NUMBER;
	}
}