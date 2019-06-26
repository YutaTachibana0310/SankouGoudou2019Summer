//=============================================================================
//
// タイトルロゴ画面処理 [titleLogoUI.cpp]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "titleLogoUI.h"
#include "UIdrawer.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define SIZE_TITLELOGO		(D3DXVECTOR3(SCREEN_WIDTH/4,SCREEN_HEIGHT/4,0.0f))
#define POSITION_TITLELOGO	(D3DXVECTOR3(SCREEN_WIDTH/2,SCREEN_HEIGHT/3,0.0f))

//*****************************************************************************
// グローバル変数
//*****************************************************************************
OBJECT	titleLogo;

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitTitleLogo(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	LoadTexture(pDevice, ADRESS_TEXTURE_TITLELOGO, &titleLogo);
	InitialTexture(&titleLogo);
	MakeVertexObject(&titleLogo);

	titleLogo.position	= POSITION_TITLELOGO;
	titleLogo.size		= SIZE_TITLELOGO;
	titleLogo.rotation	= D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	SetColorObject(&titleLogo, SET_COLOR_NOT_COLORED);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitTitleLogo(void)
{
	ReleaseTexture(&titleLogo);
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateTitleLogo(void)
{
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawTitleLogo(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	DrawObject(pDevice, titleLogo);
	SetVertexObject(&titleLogo);
}
