//=============================================================================
//
// GameシーンUI管理処理 [GameSceneUIManager.cpp]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "guageUI.h"
#include "scoreUI.h"
#include "starUI.h"
#include "comboUI.h"
#include "lineUI.h"
#include "trailUI.h"
#include "cursorUI.h"
#include "battleStartTelop.h"
#include "stageClearTelop.h"
#include "telopBG.h"
#include "GameSceneUIManager.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define GAME_SCENE_UI_MAX (10)

//*****************************************************************************
// グローバル変数
//*****************************************************************************
GameSceneUI *gameSceneUI[GAME_SCENE_UI_MAX];

//=============================================================================
// 初期化処理
//=============================================================================
void GameSceneUI::Init(void)
{
	//インスタンスの生成
	GameSceneUI *gameSceneUI[] = {
		new Guage(),new Score(),new Star(),new Combo(),
		new Line(),new Trail(),new Cursor(),new TelopBG(),
		new BattleStartTelop(),new StageClearTelop()
	};

	for (int i = 0; i < GAME_SCENE_UI_MAX; i++)
	{
		gameSceneUI[i]->Init();
	}
}

//=============================================================================
// 終了処理
//=============================================================================
void GameSceneUI::Uninit(void)
{
	for (int i = 0; i < GAME_SCENE_UI_MAX; i++)
	{
		gameSceneUI[i]->Uninit();
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void GameSceneUI::Update(HWND hWnd)
{
	for (int i = 0; i < GAME_SCENE_UI_MAX; i++)
	{ 
		gameSceneUI[i]->Update(hWnd);
	}

#ifdef _DEBUG
	// デバッグ用コマンド
	if (GetKeyboardTrigger(DIK_1))
	{
		guage->ChangeGuage(-10);
	}
	if (GetKeyboardTrigger(DIK_2))
	{
		guage->ChangeGuage(10);
	}
	if (GetKeyboardTrigger(DIK_3))
	{
		combo->AddCombo(1);
	}
	if (GetKeyboardTrigger(DIK_4))
	{
		score->AddScore(1000);
	}
	if (GetKeyboardTrigger(DIK_5))
	{
		combo->SetCombo(0);
	}
	if (GetKeyboardTrigger(DIK_6))
	{
		battleStartTelop->SetBattleStartTelop();
	}
	if (GetKeyboardTrigger(DIK_7))
	{
		stageClearTelop->SetStageClearTelop();
	}
#endif
}

//=============================================================================
// 描画処理
//=============================================================================
void GameSceneUI::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, true);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	for (int i = 0; i < GAME_SCENE_UI_MAX; i++)
	{
		gameSceneUI[i]->Draw();
	}

	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, false);
}

