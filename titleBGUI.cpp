//=============================================================================
//
// タイトル背景画面処理 [titleBGUI.cpp]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "titleBGUI.h"
#include "UIdrawer.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define SIZE_TITLEBG		(D3DXVECTOR3(SCREEN_WIDTH/2,SCREEN_HEIGHT/2,0.0f))
#define POSITION_TITLEBG	(D3DXVECTOR3(SCREEN_WIDTH/2,SCREEN_HEIGHT/2,0.0f))

//*****************************************************************************
// グローバル変数
//*****************************************************************************
OBJECT	titleBG;

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitTitleBG(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	LoadTexture(pDevice, ADRESS_TEXTURE_TITLEBG, &titleBG);
	InitialTexture(&titleBG);
	MakeVertexObject(&titleBG);

	titleBG.position	= POSITION_TITLEBG;
	titleBG.size		= SIZE_TITLEBG;
	titleBG.rotation	= D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	SetColorObject(&titleBG, SET_COLOR_NOT_COLORED);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitTitleBG(void)
{
	ReleaseTexture(&titleBG);
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateTitleBG(void)
{
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawTitleBG(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	DrawObject(pDevice, titleBG);
	SetVertexObject(&titleBG);
}
