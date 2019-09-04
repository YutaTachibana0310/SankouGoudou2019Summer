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
#define INITIALVALUE_GUAGEPERCENTAGE (1.0f)
#define SIZE_GUAGE_BG		(D3DXVECTOR3(250.0f,25.0f,0.0f))
#define SIZE_GUAGE			(D3DXVECTOR3(190.0f,25.0f,0.0f))
#define POSITION_GUAGE		(D3DXVECTOR3(SCREEN_WIDTH / 10*7.63f, SCREEN_HEIGHT / 10*1.0f, 0.0f))
#define POSITION_BG_GUAGE		(D3DXVECTOR3(SCREEN_WIDTH / 10*8.0f, SCREEN_HEIGHT / 10*1.0f, 0.0f))

//*****************************************************************************
// コンストラクタ
//*****************************************************************************
Guage::Guage()
{
	damageGuage = new GuageObject();
	hPGuage = new GuageObject();
	frame = new Object();
	bg = new Object();

	damageGuage->LoadTexture("data/TEXTURE/UI/HP/guageBody.png");
	hPGuage->LoadTexture("data/TEXTURE/UI/HP/guageBody.png");
	frame->LoadTexture("data/TEXTURE/UI/HP/guageFrame.png");
	bg->LoadTexture("data/TEXTURE/UI/HP/guageBG.png");

	damageGuage->MakeVertex(damageGuagePercentage, WIDTH_GUAGEFLAME);
	hPGuage->MakeVertex(trueGuagePercentage, WIDTH_GUAGEFLAME);
	frame->MakeVertex();
	bg->MakeVertex();

	damageGuage->position = POSITION_GUAGE;
	hPGuage->position = POSITION_GUAGE;
	frame->position = POSITION_GUAGE;
	bg->position = POSITION_BG_GUAGE;

	damageGuage->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	hPGuage->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	frame->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	bg->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	damageGuage->size = SIZE_GUAGE;
	hPGuage->size = SIZE_GUAGE;
	frame->size = SIZE_GUAGE;
	bg->size = SIZE_GUAGE_BG;

	//　色設定
	damageGuage->SetColorObject(SET_COLOR_RED);
	hPGuage->SetColorObject(SET_COLOR_NOT_COLORED);
	frame->SetColorObject(SET_COLOR_NOT_COLORED);
	bg->SetColorObject(SET_COLOR_NOT_COLORED);

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

	delete frame;
	frame = NULL;

	delete bg;
	bg = NULL;
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
	bg->Draw();
	damageGuage->Draw();
	hPGuage->Draw();
	frame->Draw();

	// 頂点座標の設定
	damageGuage->SetVertex(damageGuagePercentage, WIDTH_GUAGEFLAME, damageGuage->LEFT_GUAGEBAR);
	hPGuage->SetVertex(trueGuagePercentage,	WIDTH_GUAGEFLAME, hPGuage->LEFT_GUAGEBAR);
	frame->SetVertex();
	bg->SetVertex();
}
