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
Object titleBG;

//=============================================================================
// 初期化処理
//=============================================================================
void TitleBG::Init(void)
{
	//LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//object->LoadTexture(pDevice, ADRESS_TEXTURE_TITLEBG, &titleBG);
	//object->InitialTexture(&titleBG);
	//object->MakeVertexObject(&titleBG);

	//titleBG.position	= POSITION_TITLEBG;
	//titleBG.size		= SIZE_TITLEBG;
	//titleBG.rotation	= D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//object->SetColorObject(&titleBG, SET_COLOR_NOT_COLORED);
}

//=============================================================================
// 終了処理
//=============================================================================
void TitleBG::Uninit(void)
{
	//object->ReleaseTexture(&titleBG);
}

//=============================================================================
// 更新処理
//=============================================================================
void TitleBG:: Update(void)
{
}

//=============================================================================
// 描画処理
//=============================================================================
void TitleBG::Draw(void)
{
	//LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//object->DrawObject(pDevice, &titleBG);
	//object->SetVertexObject(&titleBG);
}
