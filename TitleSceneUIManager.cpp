//=============================================================================
//
// TitleシーンUI管理処理 [TitleSceneUIManager.cpp]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "titleBGUI.h"
#include "titleLogoUI.h"
#include "startButtonUI.h"
#include "cursorUI.h"
#include "TitleSceneUIManager.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TITLE_SCENE_UI_MAX (3)

//*****************************************************************************
// グローバル変数
//*****************************************************************************
TitleSceneUI *titleSceneUI[TITLE_SCENE_UI_MAX];

//=============================================================================
// 初期化処理
//=============================================================================
void TitleSceneUI::Init(void)
{
	//インスタンスの生成
	TitleSceneUI *titleSceneUI[] = {
		new TitleBG(), new TitleLogo(), new StartButton(),
	};

	for (int i = 0; i < TITLE_SCENE_UI_MAX; i++)
	{
		titleSceneUI[i]->Init();
	}
}

//=============================================================================
// 終了処理
//=============================================================================
void TitleSceneUI::Uninit(void)
{
	for (int i = 0; i < TITLE_SCENE_UI_MAX; i++)
	{
		titleSceneUI[i]->Uninit();
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void TitleSceneUI::Update(HWND hWnd)
{
	for (int i = 0; i < TITLE_SCENE_UI_MAX; i++)
	{
		titleSceneUI[i]->Update(hWnd);
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void TitleSceneUI::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, true);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	for (int i = 0; i < TITLE_SCENE_UI_MAX; i++)
	{
		titleSceneUI[i]->Draw();
	}

	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, false);
}

