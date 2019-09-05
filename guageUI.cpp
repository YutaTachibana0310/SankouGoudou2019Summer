//=============================================================================
//
// ゲージ画面処理 [guage.cpp]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "UIdrawer.h"
#include "debugWindow.h"
#include "Viewer3D.h"
#include "guageUI.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define WIDTH_GUAGEFLAME	(3.5f)
#define DECREASESPEED_GUAGE (0.0050f)
#define INITIALVALUE_GUAGEPERCENTAGE (1.0f)
#define SIZE_GUAGE			(D3DXVECTOR3(190.0f,25.0f,0.0f))
#define SIZE_GUAGE_BG		(D3DXVECTOR3(250.0f,25.0f,0.0f))

////座標設定(2D)
//#define POSITION_GUAGE	(D3DXVECTOR3(SCREEN_WIDTH / 10*7.63f, SCREEN_HEIGHT / 10*1.0f, 0.0f))
//#define POSITION_BG_GUAGE	(D3DXVECTOR3(SCREEN_WIDTH / 10*8.0f, SCREEN_HEIGHT / 10*1.0f, 0.0f))

//座標設定(3D)
#define POSITION_GUAGE		(D3DXVECTOR3(190.0f,25.0f,0.0f))
#define POSITION_BG_GUAGE	(D3DXVECTOR3(250.0f,25.0f,0.0f))

//*****************************************************************************
// コンストラクタ
//*****************************************************************************
Guage::Guage()
{
	//ダメージゲージ
	damageGuage = new GuageObject();
	damageGuage->LoadTexture("data/TEXTURE/UI/HP/guageBody.png");
	damageGuage->MakeVertex(damageGuagePercentage, WIDTH_GUAGEFLAME);
	damageGuage->position = POSITION_GUAGE/2;
	damageGuage->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	damageGuage->size = SIZE_GUAGE/2;
	damageGuage->SetColorObject(SET_COLOR_RED);

	//HPゲージ
	hPGuage = new GuageObject();
	hPGuage->LoadTexture("data/TEXTURE/UI/HP/guageBody.png");
	hPGuage->MakeVertex(trueGuagePercentage, WIDTH_GUAGEFLAME);
	hPGuage->position = POSITION_GUAGE/2;
	hPGuage->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	hPGuage->size = SIZE_GUAGE/2;
	hPGuage->SetColorObject(SET_COLOR_NOT_COLORED);

	//ゲージフレーム
	frame = new Object();
	frame->LoadTexture("data/TEXTURE/UI/HP/guageFrame.png");
	frame->MakeVertex();
	frame->position = POSITION_GUAGE/2;
	frame->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	frame->size = SIZE_GUAGE/2;
	frame->SetColorObject(SET_COLOR_NOT_COLORED);

	//ゲージ背景
	bg = new Object();
	bg->LoadTexture("data/TEXTURE/UI/HP/guageBG.png");
	bg->MakeVertex();
	bg->position = POSITION_BG_GUAGE/2;
	bg->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	bg->size = SIZE_GUAGE_BG/2;
	bg->SetColorObject(SET_COLOR_NOT_COLORED);

	//ビュアー
	viewer = new Viewer3D(SIZE_GUAGE_BG.x, SIZE_GUAGE_BG.y, D3DXVECTOR2(35.0f, 8.0f));
	viewer->SetPosition(D3DXVECTOR3(95.0f, 65.0f,0.0f));
	viewer->SetRotation(0.0f, 30.0f, 0.0f);

	//初期ゲージパーセンテージ設定
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

	delete viewer;
	viewer = NULL;
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
	viewer->Begin2D();

	bg->Draw();
	damageGuage->Draw();
	hPGuage->Draw();
	frame->Draw();

	// 頂点座標の設定
	damageGuage->SetVertex(damageGuagePercentage, WIDTH_GUAGEFLAME, damageGuage->LEFT_GUAGEBAR);
	hPGuage->SetVertex(trueGuagePercentage,	WIDTH_GUAGEFLAME, hPGuage->LEFT_GUAGEBAR);
	frame->SetVertex();
	bg->SetVertex();

	viewer->End2D();
	viewer->Draw3D();
}
