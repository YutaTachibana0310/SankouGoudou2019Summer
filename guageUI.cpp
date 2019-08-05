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
#define MAX_HP				(100)
#define DECREASESPEED_GUAGE (0.0050f)
#define TEXT_GUAGE_ALPHA	(0.5f)
#define INITIALVALUE_GUAGEPERCENTAGE (1.0f)
#define SIZE_GUAGE			(D3DXVECTOR3(25.0f,250.0f,0.0f))
#define POSITION_GUAGE		(D3DXVECTOR3(SCREEN_WIDTH / 10*1.0f, SCREEN_HEIGHT / 10*7.0f, 0.0f))

//=============================================================================
// 初期化処理
//=============================================================================
void Guage::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	damageGuage->LoadTexture(pDevice, ADRESS_TEXTURE_GUAGEBAR);
	hPGuage->LoadTexture(pDevice, ADRESS_TEXTURE_GUAGEBAR);
	guageFlame->LoadTexture(pDevice, ADRESS_TEXTURE_GUAGEFLAME);
	guageText->LoadTexture(pDevice, ADRESS_TEXTURE_GUAGETEXT);

	damageGuage->MakeVertexGuageBar(damageGuagePercentage,	WIDTH_GUAGEFLAME);
	hPGuage->MakeVertexGuageBar(trueGuagePercentage,	WIDTH_GUAGEFLAME);
	guageFlame->MakeVertexObject();
	guageText->MakeVertexObject();

	damageGuage->position = POSITION_GUAGE;
	hPGuage->position = POSITION_GUAGE;
	guageFlame->position = POSITION_GUAGE;
	guageText->position = POSITION_GUAGE;

	damageGuage->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	hPGuage->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	guageFlame->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	guageText->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	damageGuage->size = SIZE_GUAGE;
	hPGuage->size = SIZE_GUAGE;
	guageFlame->size = SIZE_GUAGE;
	guageText->size = SIZE_GUAGE;
	
	damageGuage->InitialTexture();
	hPGuage->InitialTexture();
	guageFlame->InitialTexture();
	guageText->InitialTexture();

	//　色設定
	damageGuage->SetColorObject(SET_COLOR_RED);
	hPGuage->SetColorObject(SET_COLOR_YELLOW);
	guageFlame->SetColorObject(SET_COLOR_NOT_COLORED);
	guageText->SetColorObject(D3DXCOLOR(0.0f, 0.0f, 0.0f, TEXT_GUAGE_ALPHA));

	damageGuagePercentage = INITIALVALUE_GUAGEPERCENTAGE;
	trueGuagePercentage   = INITIALVALUE_GUAGEPERCENTAGE;
}

//=============================================================================
// 終了処理
//=============================================================================
void Guage::Uninit(void)
{
	damageGuage->ReleaseTexture();
	hPGuage->ReleaseTexture();
	guageFlame->ReleaseTexture();
	guageText->ReleaseTexture();
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
}

//=============================================================================
// 描画処理
//=============================================================================
void Guage::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	damageGuage->DrawObject(pDevice);
	hPGuage->DrawObject(pDevice);
	guageFlame->DrawObject(pDevice);
	guageText->DrawObject(pDevice);

	// 頂点座標の設定
	damageGuage->SetVertexGuageBar(damageGuagePercentage, WIDTH_GUAGEFLAME, DOWN_GUAGEBAR);
	hPGuage->SetVertexGuageBar(trueGuagePercentage,	WIDTH_GUAGEFLAME, DOWN_GUAGEBAR);
	guageFlame->SetVertexObject();
	guageText->SetVertexObject();
}

//=============================================================================
// HPの変更
//=============================================================================
void Guage::ChangeGuage(float value)
{
	trueGuagePercentage += (value /= MAX_HP);

	// あふれ防止
	if (trueGuagePercentage	<= 0.0f)
	{
		trueGuagePercentage = 0.0f;
	}
	if (trueGuagePercentage >= INITIALVALUE_GUAGEPERCENTAGE)
	{
		trueGuagePercentage	= INITIALVALUE_GUAGEPERCENTAGE;
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
