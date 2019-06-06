//=============================================================================
//
// UI管理処理 [UIManager.cpp]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "guage.h"
#include "score.h"
#include "star.h"
#include "combo.h"
#include "line.h"

//=============================================================================
// 初期化処理
//=============================================================================
void InitUIManager(void)
{
	InitGuageParts();
	InitScore();
	InitStar();
	InitCombo();
	InitLine();
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitUIManager(void)
{
	UninitGuageParts();
	UninitScore();
	UninitStar();
	UninitCombo();
	UninitLine();
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateUIManager(HWND hWnd)
{
	UpdateGuageParts();
	UpdateScore();
	UpdateStar(hWnd);
	UpdateCombo();
	UpdateLine();

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
		ChangeCombo(1);
	}
	if (GetKeyboardTrigger(DIK_4))
	{
		ChangeScore(1000);
	}
#endif

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawUIManager(void)
{
	DrawGuageParts();
	DrawScore();
	DrawStar();
	DrawCombo();
	DrawLine();
}

