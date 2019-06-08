//=============================================================================
//
// 移動履歴画面処理 [trail.cpp]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "trail.h"
#include "UIdrawer.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	TRAILPARTS_MAX			(6)
#define SIZE_X_TRAIL			(100.0f)
#define SIZE_Y_TRAIL			(100.0f)
#define POSITION_TRAIL (D3DXVECTOR3(SCREEN_WIDTH/10*9,SCREEN_HEIGHT/10*5,0.0f))

//*****************************************************************************
// グローバル変数
//*****************************************************************************
OBJECT	trail[TRAILPARTS_MAX];

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitTrail(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// テクスチャ読み込み
	LoadTexture(pDevice, ADRESS_TEXTURE_TRAIL_BG, &trail[TRAIL_BG]);
	LoadTexture(pDevice, ADRESS_TEXTURE_TRAIL_LINE_TOP_TO_LOWERLELEFT, &trail[TRAIL_LINE_TOP_TO_LOWERLELEFT]);
	LoadTexture(pDevice, ADRESS_TEXTURE_TRAIL_LINE_TOP_TO_LOWERRIGHT, &trail[TRAIL_LINE_TOP_TO_LOWERRIGHT]);
	LoadTexture(pDevice, ADRESS_TEXTURE_TRAIL_LINE_LOWERLELEFT_TO_MIDDLERIGHT, &trail[TRAIL_LINE_LOWERLELEFT_TO_MIDDLERIGHT]);
	LoadTexture(pDevice, ADRESS_TEXTURE_TRAIL_LINE_LOWERRIGHT_TO_MIDDLELEFT, &trail[TRAIL_LINE_LOWERRIGHT_TO_MIDDLELEFT]);
	LoadTexture(pDevice, ADRESS_TEXTURE_TRAIL_LINE_MIDDLELEFT_TO_MIDDLERIGHT, &trail[TRAIL_LINE_MIDDLELEFT_TO_MIDDLERIGHT]);

	for (int i = 0; i < TRAILPARTS_MAX; i++)
	{
		InitialTexture(&trail[i]);
		MakeVertexObject(&trail[i]);

		trail[i].position = POSITION_TRAIL;
		trail[i].size = D3DXVECTOR3(SIZE_X_TRAIL, SIZE_Y_TRAIL, 0.0f);
		trail[i].rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		SetColorObject(&trail[i], SET_COLOR_NOT_COLORED);
	}
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitTrail(void)
{
	for (int i = 0; i < TRAILPARTS_MAX; i++)
	{
		ReleaseTexture(&trail[i]);
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateTrail(void)
{
	for (int i = 0; i < TRAILPARTS_MAX; i++)
	{
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawTrail(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int i = 0; i < TRAILPARTS_MAX; i++)
	{
		DrawObject(pDevice, trail[i]);
		SetVertexObject(&trail[i]);
	}
}
