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

//=============================================================================
// 初期化処理
//=============================================================================
void InitUIManager(void)
{
	InitGuageParts();
	InitScore();
	InitStar();
	InitCombo();
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
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, true);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	DrawGuageParts();
	DrawScore();
	DrawStar();
	DrawCombo();

	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, false);
}

