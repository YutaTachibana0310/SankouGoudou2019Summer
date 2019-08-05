//=============================================================================
//
// スタートボタン画面処理 [startButtonPartsUI.cpp]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "startButtonUI.h"
#include "UIdrawer.h"
#include "TitleSceneUIManager.h"

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
// グローバル変数
//*****************************************************************************
Object	startButtonParts[STARTBUTTON_PARTS_MAX];
StartButtonManager startButtonManager;
bool	IsAlphaIncreased = true;
float	alpha = 0;

//=============================================================================
// 初期化処理
//=============================================================================
void StartButton::Init(void)
{
	//LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//object->LoadTexture(pDevice, ADRESS_TEXTURE_STARTBUTTON_BG, &startButtonParts[BACKGROUND_STARTBUTTON]);
	//object->LoadTexture(pDevice, ADRESS_TEXTURE_STARTBUTTON_TEXT, &startButtonParts[TEXT_STARTBUTTON]);

	//for (int i = 0; i < STARTBUTTON_PARTS_MAX; i++)
	//{
	//	object->InitialTexture(&startButtonParts[i]);
	//	object->MakeVertexObject(&startButtonParts[i]);

	//	startButtonParts[i].position		= POSITION_STARTBUTTON;
	//	startButtonParts[i].size			= SIZE_STARTBUTTON;
	//	startButtonParts[i].rotation		= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//	startButtonParts[i].colliderSize	= COLLIDER_SIZE_STARTBUTTON;
	//}

	//object->SetColorObject(&startButtonParts[BACKGROUND_STARTBUTTON], SET_COLOR_NOT_COLORED);
	//object->SetColorObject(&startButtonParts[TEXT_STARTBUTTON], SET_COLOR_NOT_COLORED);
}

//=============================================================================
// 終了処理
//=============================================================================
void StartButton::Uninit(void)
{
	//for (int i = 0; i < STARTBUTTON_PARTS_MAX; i++)
	//{
	//	object->ReleaseTexture(&startButtonParts[i]);
	//}
}

//=============================================================================
// 更新処理
//=============================================================================
void StartButton::Update(HWND hWnd)
{
	//if (IsMouseOvered(hWnd,startButtonParts[BACKGROUND_STARTBUTTON].position, 
	//	startButtonParts[BACKGROUND_STARTBUTTON].colliderSize))
	//{
	//	// ボタンを押したらゲームシーンへ
	//	if (IsMouseLeftTriggered())
	//	{
	//		startButtonManager.GoGameScene();
	//	}

	//	for (int i = 0; i < STARTBUTTON_PARTS_MAX; i++)
	//	{
	//		// 選択されているなら拡大表示
	//		startButtonParts[i].size.x = SIZE_STARTBUTTON.x + VOLUME_ZOOM;
	//		startButtonParts[i].size.y = SIZE_STARTBUTTON.y + VOLUME_ZOOM;
	//	}
	//}
	//else
	//{	
	//	for (int i = 0; i < STARTBUTTON_PARTS_MAX; i++)
	//	{
	//		// 元に戻す
	//		startButtonParts[i].size.x = SIZE_STARTBUTTON.x;
	//		startButtonParts[i].size.y = SIZE_STARTBUTTON.y;
	//	}
	//}

	//BlinkStartButtonText();
}

//=============================================================================
// 描画処理
//=============================================================================
void StartButton::Draw(void)
{
	//LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//for (int i = 0; i < STARTBUTTON_PARTS_MAX; i++)
	//{
	//	object->DrawObject(pDevice, &startButtonParts[i]);
	//	object->SetVertexObject(&startButtonParts[i]);
	//}
}

//=============================================================================
// スタートボタンテキスト点滅処理
//=============================================================================
void StartButton::BlinkStartButtonText(void)
{
	//if (alpha >= 1.0f)
	//{
	//	IsAlphaIncreased = false;
	//}
	//if (alpha <= 0.0f)
	//{
	//	IsAlphaIncreased = true;
	//}

	//if (IsAlphaIncreased)
	//{
	//	alpha += INCREASE_VOLUME_ALPHA;
	//}
	//else
	//{
	//	alpha -= INCREASE_VOLUME_ALPHA;
	//}

	//object->SetColorObject(&startButtonParts[TEXT_STARTBUTTON], D3DXCOLOR(1.0f,1.0f,1.0f,alpha));
}

//=============================================================================
// マウスオーバー判定処理
//=============================================================================
bool StartButton::IsMouseOvered(HWND hWnd, D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	size /= 2.0f;	// 半サイズにする

	D3DXVECTOR2 mouseColliderSize = D3DXVECTOR2(2.5f, 2.5f);

	if (GetMousePosition(hWnd).x + mouseColliderSize.x > pos.x - size.x
		&& pos.x + size.x > GetMousePosition(hWnd).x - mouseColliderSize.x
		&&
		GetMousePosition(hWnd).y + mouseColliderSize.y > pos.y - size.y
		&& pos.y + size.y > GetMousePosition(hWnd).y - mouseColliderSize.y)
	{
		return true;
	}

	return false;
}
