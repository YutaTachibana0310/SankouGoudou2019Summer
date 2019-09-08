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
// コンストラクタ
//*****************************************************************************
TitleBG::TitleBG()
{
	titleBG = new Object();

	titleBG->LoadTexture("data/TEXTURE/UI/titleBG.jpg");
	titleBG->MakeVertex();

	titleBG->position = POSITION_TITLEBG;
	titleBG->size = SIZE_TITLEBG;
	titleBG->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	titleBG->SetColorObject(SET_COLOR_NOT_COLORED);
}

//*****************************************************************************
// デストラクタ
//*****************************************************************************
TitleBG::~TitleBG()
{
	SAFE_DELETE(titleBG);
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
	titleBG->Draw();
	titleBG->SetVertex();
}
