//=============================================================================
//
// リザルト背景画面処理 [resultBGUI.cpp]
// Author : 渡邉良則（おおはま変更）
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
// コンストラクタ
//*****************************************************************************
ResultBG::ResultBG()
{
	resultBG = new Object();

	resultBG->LoadTexture("data/TEXTURE/UI/Result/ブラック.jpg");
	resultBG->MakeVertex();

	resultBG->position = POSITION_RESULTBG;
	resultBG->size = SIZE_RESULTBG;
	resultBG->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	resultBG->SetColorObject(SET_COLOR_NOT_COLORED);
}

//*****************************************************************************
// デストラクタ
//*****************************************************************************
ResultBG::~ResultBG()
{
	delete resultBG;
	resultBG = NULL;
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
	resultBG->Draw();
	resultBG->SetVertex();
}
