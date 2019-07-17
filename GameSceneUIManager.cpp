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

//=============================================================================
// 初期化処理
//=============================================================================
void InitGameSceneUI(void)
{
	InitGuageParts();
	InitScore();
	InitStar();
	InitCombo();
	InitLine();
	InitTrail();
	InitCursor();
	InitTelopBG();

	InitBattleStartTelop();
	InitStageClearTelop();
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitGameSceneUI(void)
{
	UninitGuageParts();
	UninitScore();
	UninitStar();
	UninitCombo();
	UninitLine();
	UninitTrail();
	UninitCursor();
	UninitTelopBG();

	UninitBattleStartTelop();
	UninitStageClearTelop();
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateGameSceneUI(HWND hWnd)
{
	UpdateGuageParts();
	UpdateScore();
	UpdateStar();
	UpdateCombo();
	UpdateLine();
	UpdateTrail();
	UpdateCursor(hWnd);
	UpdateTelopBG();

	UpdateBattleStartTelop();
	UpdateStageClearTelop();

#ifdef _DEBUG
	// デバッグ用コマンド
	if (GetKeyboardTrigger(DIK_1))
	{
		ChangeGuage(-10);
	}
	if (GetKeyboardTrigger(DIK_2))
	{
		ChangeGuage(10);
	}
	if (GetKeyboardTrigger(DIK_3))
	{
		AddCombo(1);
	}
	if (GetKeyboardTrigger(DIK_4))
	{
		AddScore(1000);
	}
	if (GetKeyboardTrigger(DIK_5))
	{
		SetCombo(0);
	}
	if (GetKeyboardTrigger(DIK_6))
	{
		SetBattleStartTelop();
	}
	if (GetKeyboardTrigger(DIK_7))
	{
		SetStageClearTelop();
	}
#endif
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawGameSceneUI(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, true);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	DrawGuageParts();
	DrawScore();
	DrawStar();
	DrawLine();
	DrawCombo();
	DrawTrail();

	DrawCursor();
	DrawTelopBG();

	DrawBattleStartTelop();
	DrawStageClearTelop();
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, false);
}

