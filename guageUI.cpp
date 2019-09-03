//=============================================================================
//
// ゲージ画面処理 [guage.cpp]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "guageUI.h"
#include "UIdrawer.h"
#include "debugWindow.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	GUAGEPARTS_MAX		(4)
#define WIDTH_GUAGEFLAME	(5.0f)
#define DECREASESPEED_GUAGE (0.0050f)
#define TEXT_GUAGE_ALPHA	(0.5f)
#define INITIALVALUE_GUAGEPERCENTAGE (1.0f)
#define SIZE_GUAGE			(D3DXVECTOR3(25.0f,250.0f,0.0f))
#define POSITION_GUAGE		(D3DXVECTOR3(SCREEN_WIDTH / 10*1.0f, SCREEN_HEIGHT / 10*7.0f, 0.0f))

//*****************************************************************************
// コンストラクタ
//*****************************************************************************
Guage::Guage()
{
	damageGuage = new GuageObject();
	hPGuage = new GuageObject();
	flame = new Object();
	text = new Object();

	damageGuage->LoadTexture("data/TEXTURE/UI/guage/guageBar_vertical.png");
	hPGuage->LoadTexture("data/TEXTURE/UI/guage/guageBar_vertical.png");
	flame->LoadTexture("data/TEXTURE/UI/guage/guageFrame_vertical.png");
	text->LoadTexture("data/TEXTURE/UI/guage/guageText_fever_vertical.png");

	damageGuage->MakeVertex(damageGuagePercentage, WIDTH_GUAGEFLAME);
	hPGuage->MakeVertex(trueGuagePercentage, WIDTH_GUAGEFLAME);
	flame->MakeVertex();
	text->MakeVertex();

	damageGuage->position = POSITION_GUAGE;
	hPGuage->position = POSITION_GUAGE;
	flame->position = POSITION_GUAGE;
	text->position = POSITION_GUAGE;

	damageGuage->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	hPGuage->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	flame->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	text->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	damageGuage->size = SIZE_GUAGE;
	hPGuage->size = SIZE_GUAGE;
	flame->size = SIZE_GUAGE;
	text->size = SIZE_GUAGE;

	//　色設定
	damageGuage->SetColorObject(SET_COLOR_RED);
	hPGuage->SetColorObject(SET_COLOR_YELLOW);
	flame->SetColorObject(SET_COLOR_NOT_COLORED);
	text->SetColorObject(D3DXCOLOR(0.0f, 0.0f, 0.0f, TEXT_GUAGE_ALPHA));

	damageGuagePercentage = INITIALVALUE_GUAGEPERCENTAGE;
	trueGuagePercentage = INITIALVALUE_GUAGEPERCENTAGE;
}

//*****************************************************************************
// デストラクタ
//*****************************************************************************
Guage::~Guage()
{
	delete damageGuage;
	damageGuage = NULL;

	delete hPGuage;
	hPGuage = NULL;

	delete flame;
	flame = NULL;

	delete text;
	text = NULL;

}

//=============================================================================
// 更新処理
//=============================================================================
void Guage::Update(void)
{
	//ダメージ表現ゲージパーセンテージが実際のゲージパーセンテージと同じになるまで減算
	if (damageGuagePercentage > trueGuagePercentage)
	{
		damageGuagePercentage -= DECREASESPEED_GUAGE;
	}
	if (damageGuagePercentage < trueGuagePercentage)
	{
		damageGuagePercentage = trueGuagePercentage;
	}

	// あふれ防止
	if (trueGuagePercentage <= 0.0f)
	{
		trueGuagePercentage = 0.0f;
	}
	if (trueGuagePercentage >= INITIALVALUE_GUAGEPERCENTAGE)
	{
		trueGuagePercentage = INITIALVALUE_GUAGEPERCENTAGE;
	}
	if (damageGuagePercentage <= 0.0f)
	{
		damageGuagePercentage = 0.0f;
	}
	if (damageGuagePercentage >= INITIALVALUE_GUAGEPERCENTAGE)
	{
		damageGuagePercentage = INITIALVALUE_GUAGEPERCENTAGE;
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void Guage::Draw(void)
{
	damageGuage->Draw();
	hPGuage->Draw();
	flame->Draw();
	text->Draw();

	// 頂点座標の設定
	damageGuage->SetVertex(damageGuagePercentage, WIDTH_GUAGEFLAME, damageGuage->DOWN_GUAGEBAR);
	hPGuage->SetVertex(trueGuagePercentage,	WIDTH_GUAGEFLAME, hPGuage->DOWN_GUAGEBAR);
	flame->SetVertex();
	text->SetVertex();
}
