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
#include "trailUI.h"

using namespace std;

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MOVETARGET_LENGTH				(6)
#define PLAYER_DISTANCE_FROM_CAMERA		(150.0f)

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void CheckInput(HWND hWnd);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
PlayerObserver *observer;
TrailCollider *testCollider;

//*****************************************************************************
// 初期化処理
//*****************************************************************************
HRESULT InitPlayerController(void)
{
	observer = new PlayerObserver();
	observer->Init();

	testCollider = new TrailCollider("Enemy");
	testCollider->RegisterToCheckList();

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

	vector<int> test;
	GetPlayerMoveHistory(&test);

	static int start, end;
	static float posZ = 500.0f;
	BeginDebugWindow("Collider");

	DebugInputInt("Start", &start);
	DebugInputInt("End", &end);
	DebugSliderFloat("Z", &posZ, 0.0f, 1000.0f);

	testCollider->SetAddressZ(&posZ);
	testCollider->SetTrailIndex(LineTrailModel(start, end));

	EndDebugWindow("Collider");
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
// MoveHistory取得処理
//=============================================================================
void GetPlayerMoveHistory(vector<int> *pOut)
{
	//移動履歴を取得
	vector<LineTrailModel> moveHistory;
	observer->model->GetAllPlayerTrail(&moveHistory);

	//UI用データに変換
	for (LineTrailModel model : moveHistory)
	{
		if (model.start == TOP || model.end == TOP)
		{
			if (model.start == LOWER_RIGHT || model.end == LOWER_RIGHT)
			{
				pOut->push_back(TRAIL_LINE_TOP_TO_LOWERRIGHT);
				continue;
			}
			if (model.start == LOWER_LEFT || model.end == LOWER_LEFT)
			{
				pOut->push_back(TRAIL_LINE_TOP_TO_LOWERLEFT);
				continue;
			}
		}
		else if (model.start == LOWER_LEFT || model.end == LOWER_LEFT)
		{
			if (model.start == MIDDLE_RIGHT || model.end == MIDDLE_RIGHT)
			{
				pOut->push_back(TRAIL_LINE_LOWERLEFT_TO_MIDDLERIGHT);
				continue;
			}
		}
		else if (model.start == LOWER_RIGHT || model.end == LOWER_RIGHT)
		{
			if (model.start == MIDDLE_LEFT || model.end == MIDDLE_LEFT)
			{
				pOut->push_back(TRAIL_LINE_LOWERRIGHT_TO_MIDDLELEFT);
				continue;
			}
		}
		else if (model.start == MIDDLE_LEFT || model.end == MIDDLE_LEFT)
		{
			if (model.start == MIDDLE_RIGHT || model.end == MIDDLE_RIGHT)
			{
				pOut->push_back(TRAIL_LINE_MIDDLELEFT_TO_MIDDLERIGHT);
				continue;
			}
		}
	}

	return;
}