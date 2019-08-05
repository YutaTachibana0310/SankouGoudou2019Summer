//=============================================================================
//
// リザルト背景画面処理 [resultBGUI.cpp]
// Author : 渡邉良則
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "resultBGUI.h"
#include "UIdrawer.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define SIZE_RESULTBG		(D3DXVECTOR3(SCREEN_WIDTH/2,SCREEN_HEIGHT/2,0.0f))
#define POSITION_RESULTBG	(D3DXVECTOR3(SCREEN_WIDTH/2,SCREEN_HEIGHT/2,0.0f))

//*****************************************************************************
// グローバル変数
//*****************************************************************************
Object	resultBG;

//=============================================================================
// 初期化処理
//=============================================================================
void ResultBG::Init(void)
{
	//LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//object->LoadTexture(pDevice, ADRESS_TEXTURE_RESULTBG, &resultBG);
	//object->InitialTexture(&resultBG);
	//object->MakeVertexObject(&resultBG);

	//resultBG.position = POSITION_RESULTBG;
	//resultBG.size = SIZE_RESULTBG;
	//resultBG.rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//object->SetColorObject(&resultBG, SET_COLOR_NOT_COLORED);
}

//=============================================================================
// 終了処理
//=============================================================================
void ResultBG::Uninit(void)
{
	//object->ReleaseTexture(&resultBG);
}

//=============================================================================
// 更新処理
//=============================================================================
void ResultBG::Update(void)
{
}

//=============================================================================
// 描画処理
//=============================================================================
void ResultBG::Draw(void)
{
	//LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//object->DrawObject(pDevice, &resultBG);
	//object->SetVertexObject(&resultBG);
}
