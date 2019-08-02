//=============================================================================
//
// インターフェースライン画面処理 [line.cpp]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "lineUI.h"
#include "UIdrawer.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define SIZE_LINE		(D3DXVECTOR3(SCREEN_WIDTH/2,170.0f,0.0f))
#define POSITION_LINE	(D3DXVECTOR3(SCREEN_WIDTH/2,SCREEN_HEIGHT/10*2,0.0f))

//*****************************************************************************
// グローバル変数
//*****************************************************************************
Object line;

//=============================================================================
// 初期化処理
//=============================================================================
void Line::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	object->LoadTexture(pDevice, ADRESS_TEXTURE_LINE, &line);
	object->InitialTexture(&line);
	object->MakeVertexObject(&line);

	line.position	= POSITION_LINE;
	line.size		= SIZE_LINE;
	line.rotation	= D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	object->SetColorObject(&line, SET_COLOR_NOT_COLORED);
}

//=============================================================================
// 終了処理
//=============================================================================
void Line::Uninit(void)
{
	object->ReleaseTexture(&line);
}

//=============================================================================
// 更新処理
//=============================================================================
void Line::Update()
{
}

//=============================================================================
// 描画処理
//=============================================================================
void Line::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	object->DrawObject(pDevice, &line);
	object->SetVertexObject(&line);
}
