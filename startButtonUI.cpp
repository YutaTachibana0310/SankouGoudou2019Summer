//=============================================================================
//
// スタートボタン画面処理 [startButtonPartsUI.cpp]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#include "main.h"
#include "Game.h"
#include "input.h"
#include "startButtonUI.h"
#include "cursorUI.h"
#include "masktex.h"
#include "UIdrawer.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define STARTBUTTON_PARTS_MAX		(2)
#define SIZE_STARTBUTTON			(D3DXVECTOR3(SCREEN_WIDTH/10,SCREEN_HEIGHT/10,0.0f))
#define COLLIDER_SIZE_STARTBUTTON	(D3DXVECTOR3(320.0f,100.0f,0.0f))
#define POSITION_STARTBUTTON		(D3DXVECTOR3(SCREEN_WIDTH/2,SCREEN_HEIGHT/10*8,0.0f))
#define VOLUME_ZOOM					(30.0f)
#define INCREASE_VOLUME_ALPHA		(0.02f)

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void BlinkStartButtonText(void);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
OBJECT	startButtonParts[STARTBUTTON_PARTS_MAX];
bool	IsAlphaIncreased = true;
float	alpha = 0;

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitStartButton(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	LoadTexture(pDevice, ADRESS_TEXTURE_STARTBUTTON_BG, &startButtonParts[BACKGROUND_STARTBUTTON]);
	LoadTexture(pDevice, ADRESS_TEXTURE_STARTBUTTON_TEXT, &startButtonParts[TEXT_STARTBUTTON]);

	for (int i = 0; i < STARTBUTTON_PARTS_MAX; i++)
	{
		InitialTexture(&startButtonParts[i]);
		MakeVertexObject(&startButtonParts[i]);

		startButtonParts[i].position		= POSITION_STARTBUTTON;
		startButtonParts[i].size			= SIZE_STARTBUTTON;
		startButtonParts[i].rotation		= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		startButtonParts[i].colliderSize	= COLLIDER_SIZE_STARTBUTTON;
	}

	SetColorObject(&startButtonParts[BACKGROUND_STARTBUTTON], SET_COLOR_NOT_COLORED);
	SetColorObject(&startButtonParts[TEXT_STARTBUTTON], SET_COLOR_NOT_COLORED);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitStartButton(void)
{
	for (int i = 0; i < STARTBUTTON_PARTS_MAX; i++)
	{
		ReleaseTexture(&startButtonParts[i]);
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateStartButton(void)
{
	if (IsCursorOvered(startButtonParts[BACKGROUND_STARTBUTTON].position, 
		startButtonParts[BACKGROUND_STARTBUTTON].colliderSize))
	{
		// ボタンを押したらゲームシーンへ
		if (IsMouseLeftTriggered())
		{
			SceneChangeFlag(true, SceneGame);
		}

		for (int i = 0; i < STARTBUTTON_PARTS_MAX; i++)
		{
			// 選択されているなら拡大表示
			startButtonParts[i].size.x = SIZE_STARTBUTTON.x + VOLUME_ZOOM;
			startButtonParts[i].size.y = SIZE_STARTBUTTON.y + VOLUME_ZOOM;
		}
	}
	else
	{	
		for (int i = 0; i < STARTBUTTON_PARTS_MAX; i++)
		{
			// 元に戻す
			startButtonParts[i].size.x = SIZE_STARTBUTTON.x;
			startButtonParts[i].size.y = SIZE_STARTBUTTON.y;
		}
	}

	BlinkStartButtonText();
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawStartButton(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int i = 0; i < STARTBUTTON_PARTS_MAX; i++)
	{
		DrawObject(pDevice, startButtonParts[i]);
		SetVertexObject(&startButtonParts[i]);
	}
}

//=============================================================================
// スタートボタンテキスト点滅処理
//=============================================================================
void BlinkStartButtonText(void)
{
	if (alpha >= 1.0f)
	{
		IsAlphaIncreased = false;
	}
	if (alpha <= 0.0f)
	{
		IsAlphaIncreased = true;
	}

	if (IsAlphaIncreased)
	{
		alpha += INCREASE_VOLUME_ALPHA;
	}
	else
	{
		alpha -= INCREASE_VOLUME_ALPHA;
	}

	SetColorObject(&startButtonParts[TEXT_STARTBUTTON], D3DXCOLOR(1.0f,1.0f,1.0f,alpha));
}
