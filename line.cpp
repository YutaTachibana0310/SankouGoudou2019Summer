//=============================================================================
//
// インターフェースライン画面処理 [line.cpp]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "line.h"
#include "UIdrawer.h"
#include "collider.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define SIZE_X_LINE			(780.0f)
#define SIZE_Y_LINE			(450.0f)
#define POSITION_LINE (D3DXVECTOR3(SCREEN_WIDTH/2,SCREEN_HEIGHT/2,0.0f))

//*****************************************************************************
// グローバル変数
//*****************************************************************************
OBJECT	line;

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitLine(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	LoadTexture(pDevice, ADRESS_TEXTURE_LINE, &line);
	InitialTexture(&line);
	MakeVertexRotateObject(&line);

	line.position = POSITION_LINE;
	line.size = D3DXVECTOR3(SIZE_X_LINE, SIZE_Y_LINE, 0.0f);
	line.rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	SetColorObject(&line, SET_COLOR_NOT_COLORED);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitLine(void)
{
	ReleaseTexture(&line);
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateLine()
{
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawLine(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	DrawObject(pDevice, line);
	SetVertexObject(&line);
}
