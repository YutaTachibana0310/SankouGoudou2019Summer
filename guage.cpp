//=============================================================================
//
// ゲージ画面処理 [guage.cpp]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "guage.h"
#include "UIdrawer.h"
#include "debugWindow.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	GUAGEPARTS_MAX		(3)
#define WIDTH_GUAGEFLAME	(5.0f)
#define MAX_HP				(100)
#define DECREASESPEED_GUAGE (0.0050f)
#define SIZE_X_GUAGE		(250.0f)
#define SIZE_Y_GUAGE		(25.0f)
#define POSITION_GUAGE		(D3DXVECTOR3(SCREEN_WIDTH / 10*1.7f, SCREEN_HEIGHT / 10*2.3f, 0.0f))
#define INITIALVALUE_GUAGEPERCENTAGE (1.0f)

//*****************************************************************************
// グローバル変数
//*****************************************************************************
OBJECT	guageParts[GUAGEPARTS_MAX];
float	damageGuagePercentage;	//ダメージ表現ゲージパーセンテージ
float	trueGuagePercentage;	//実際のゲージパーセンテージ

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitGuageParts(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	LoadTexture(pDevice, ADRESS_TEXTURE_GUAGEBAR,	&guageParts[GUAGEBAR_DAMAGE]);
	LoadTexture(pDevice, ADRESS_TEXTURE_GUAGEBAR,	&guageParts[GUAGEBAR_TRUE]);
	LoadTexture(pDevice, ADRESS_TEXTURE_GUAGEFLAME, &guageParts[GUAGEFLAME]);

	MakeVertexGuageBar(&guageParts[GUAGEBAR_DAMAGE],damageGuagePercentage,	WIDTH_GUAGEFLAME);
	MakeVertexGuageBar(&guageParts[GUAGEBAR_TRUE],	trueGuagePercentage,	WIDTH_GUAGEFLAME);
	MakeVertexObject  (&guageParts[GUAGEFLAME]);

	for (int i = 0; i < GUAGEPARTS_MAX; i++)
	{
		guageParts[i].position = POSITION_GUAGE;
		guageParts[i].rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		guageParts[i].size     = D3DXVECTOR3(SIZE_X_GUAGE, SIZE_Y_GUAGE, 0.0f);

		InitialTexture(&guageParts[i]);
	}

	//　色設定
	SetColorObject(&guageParts[GUAGEBAR_DAMAGE], SET_COLOR_RED);
	SetColorObject(&guageParts[GUAGEBAR_TRUE],	 SET_COLOR_NOT_COLORED);
	SetColorObject(&guageParts[GUAGEFLAME],		 SET_COLOR_PINK);

	damageGuagePercentage = INITIALVALUE_GUAGEPERCENTAGE;
	trueGuagePercentage   = INITIALVALUE_GUAGEPERCENTAGE;

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitGuageParts(void)
{
	for (int i = 0; i < GUAGEPARTS_MAX; i++)
	{
		ReleaseTexture(&guageParts[i]);
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateGuageParts(void)
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
void DrawGuageParts(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int i = 0; i < GUAGEPARTS_MAX; i++)
	{
		DrawObject(pDevice, guageParts[i]);
	}

	// 頂点座標の設定
	SetVertexGuageBar(&guageParts[GUAGEBAR_DAMAGE],	damageGuagePercentage,	WIDTH_GUAGEFLAME);
	SetVertexGuageBar(&guageParts[GUAGEBAR_TRUE],	trueGuagePercentage,	WIDTH_GUAGEFLAME);
	SetVertexObject(&guageParts[GUAGEFLAME]);
}

//=============================================================================
// HPの変更
//=============================================================================
void ChangeGuage(float value)
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
