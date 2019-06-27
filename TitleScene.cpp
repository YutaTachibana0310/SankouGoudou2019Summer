//=====================================
//
//タイトルシーン処理[TitleScene.cpp]
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "TitleScene.h"
#include "debugWindow.h"
#include "Game.h"
#include "InputController.h"
#include "masktex.h"

/**************************************
マクロ定義
***************************************/

/**************************************
構造体定義
***************************************/

/**************************************
グローバル変数
***************************************/

/**************************************
初期化処理
***************************************/
void TitleScene::Init()
{


	InitMask();
}

/**************************************
終了処理
***************************************/
void TitleScene::Uninit()
{
	UninitMask();
}

/**************************************
更新処理
***************************************/
void TitleScene::Update(HWND hWnd)
{
	UpdateMask();
}

/**************************************
描画処理
***************************************/
void TitleScene::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, true);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	DrawMaskTEX();

	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, false);
}