//=============================================================================
//
// TitleシーンUI管理処理 [TitleSceneUIManagerManager.cpp]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "titleBGUI.h"
#include "titleLogoUI.h"
#include "startButtonUI.h"
#include "cursorUI.h"
#include "masktex.h"
#include "TitleSceneUIManager.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
//#define TITLE_SCENE_UI_MAX (3)

//*****************************************************************************
// グローバル変数
//*****************************************************************************
//TitleSceneUIManager *titleSceneUI[TITLE_SCENE_UI_MAX];

//*****************************************************************************
// コンストラクタ
//*****************************************************************************
TitleSceneUIManager::TitleSceneUIManager()
{
	startButton = new StartButton();
	titleBG = new TitleBG();
	titleLogo = new TitleLogo();
}

//*****************************************************************************
// デストラクタ
//*****************************************************************************
TitleSceneUIManager::~TitleSceneUIManager()
{
	SAFE_DELETE(startButton);
	SAFE_DELETE(titleBG);
	SAFE_DELETE(titleLogo);
}

//=============================================================================
// 初期化処理
//=============================================================================
void TitleSceneUIManager::Init()
{

}

//=============================================================================
// 終了処理
//=============================================================================
void TitleSceneUIManager::Uninit()
{

}

//=============================================================================
// 更新処理
//=============================================================================
void TitleSceneUIManager::Update(HWND hWnd)
{
	startButton->Update(hWnd);
	titleBG->Update();
	titleLogo->Update();
}

//=============================================================================
// 描画処理
//=============================================================================
void TitleSceneUIManager::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, true);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	titleBG->Draw();
	titleLogo->Draw();
	startButton->Draw();

	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, false);
}

