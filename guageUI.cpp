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

//*****************************************************************************
// グローバル変数
//*****************************************************************************
Object	guageParts[GUAGEPARTS_MAX];
float	damageGuagePercentage;	//ダメージ表現ゲージパーセンテージ
float	trueGuagePercentage;	//実際のゲージパーセンテージ

//=============================================================================
// 初期化処理
//=============================================================================
void Guage::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	object->LoadTexture(pDevice, ADRESS_TEXTURE_GUAGEBAR, &guageParts[GUAGEBAR_DAMAGE]);
	object->LoadTexture(pDevice, ADRESS_TEXTURE_GUAGEBAR, &guageParts[GUAGEBAR_TRUE]);
	object->LoadTexture(pDevice, ADRESS_TEXTURE_GUAGEFLAME, &guageParts[GUAGEFLAME]);
	object->LoadTexture(pDevice, ADRESS_TEXTURE_GUAGETEXT, &guageParts[GUAGETEXT]);

	object->MakeVertexGuageBar(&guageParts[GUAGEBAR_DAMAGE],damageGuagePercentage,	WIDTH_GUAGEFLAME);
	object->MakeVertexGuageBar(&guageParts[GUAGEBAR_TRUE],	trueGuagePercentage,	WIDTH_GUAGEFLAME);
	//object->MakeVertexObject  (&guageParts[GUAGEFLAME]);
	//object->MakeVertexObject(&guageParts[GUAGETEXT]);

	for (int i = 0; i < GUAGEPARTS_MAX; i++)
	{
		guageParts[i].position = POSITION_GUAGE;
		guageParts[i].rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		guageParts[i].size     = SIZE_GUAGE;

		object->InitialTexture(&guageParts[i]);
	}

	//　色設定
	object->SetColorObject(&guageParts[GUAGEBAR_DAMAGE], SET_COLOR_RED);
	object->SetColorObject(&guageParts[GUAGEBAR_TRUE],	 SET_COLOR_YELLOW);
	object->SetColorObject(&guageParts[GUAGEFLAME],		 SET_COLOR_NOT_COLORED);
	object->SetColorObject(&guageParts[GUAGETEXT], D3DXCOLOR(0.0f, 0.0f, 0.0f, TEXT_GUAGE_ALPHA));

	damageGuagePercentage = INITIALVALUE_GUAGEPERCENTAGE;
	trueGuagePercentage   = INITIALVALUE_GUAGEPERCENTAGE;
}

//=============================================================================
// 終了処理
//=============================================================================
void Guage::Uninit(void)
{
	for (int i = 0; i < GUAGEPARTS_MAX; i++)
	{
		object->ReleaseTexture(&guageParts[i]);
	}
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

	for (int i = 0; i < GUAGEPARTS_MAX; i++)
	{
		object->DrawObject(pDevice, &guageParts[i]);
	}

	// 頂点座標の設定
	object->SetVertexGuageBar(&guageParts[GUAGEBAR_DAMAGE],	damageGuagePercentage,	WIDTH_GUAGEFLAME, DOWN_GUAGEBAR);
	object->SetVertexGuageBar(&guageParts[GUAGEBAR_TRUE],	trueGuagePercentage,	WIDTH_GUAGEFLAME, DOWN_GUAGEBAR);
	object->SetVertexObject(&guageParts[GUAGEFLAME]);
	//SetVertexObject(&guageParts[GUAGETEXT]);
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
