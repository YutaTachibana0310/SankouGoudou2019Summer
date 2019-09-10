//=============================================================================
//
// リザルト背景画面処理 [resultBGUI.cpp]
// Author : 渡邉良則
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "resultBGUI.h"
#include "UIdrawerC.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define SIZE_RESULTBG		(D3DXVECTOR3(SCREEN_WIDTH/2,SCREEN_HEIGHT/2,0.0f))
#define POSITION_RESULTBG	(D3DXVECTOR3(SCREEN_WIDTH/2,SCREEN_HEIGHT/2,0.0f))

//*****************************************************************************
// グローバル変数
//*****************************************************************************
OBJECT	resultBG;

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitResultBG(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	LoadTexture(pDevice, ADRESS_TEXTURE_RESULTBG, &resultBG);
	InitialTexture(&resultBG);
	MakeVertexObject(&resultBG);

	resultBG.position = POSITION_RESULTBG;
	resultBG.size = SIZE_RESULTBG;
	resultBG.rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	SetColorObject(&resultBG, SET_COLOR_NOT_COLORED);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitResultBG(void)
{
	ReleaseTexture(&resultBG);
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateResultBG(void)
{
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawResultBG(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, false);

	DrawObject(pDevice, resultBG);
	SetVertexObject(&resultBG);

	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, true);
}