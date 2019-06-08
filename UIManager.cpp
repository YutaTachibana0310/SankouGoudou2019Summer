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
#include "trail.h"

//=============================================================================
// 初期化処理
//=============================================================================
void InitUI(void)
{
	InitGuageParts();
	InitScore();
	InitStar();
	InitCombo();
	InitLine();
	InitTrail();
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitUI(void)
{
	UninitGuageParts();
	UninitScore();
	UninitStar();
	UninitCombo();
	UninitLine();
	UninitTrail();
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateUI(HWND hWnd)
{
	UpdateGuageParts();
	UpdateScore();
	UpdateStar(hWnd);
	UpdateCombo();
	UpdateLine();
	UpdateTrail();

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
void DrawUI(void)
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
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, false);
}

