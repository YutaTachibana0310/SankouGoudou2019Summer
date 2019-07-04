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
#include "TitleSceneUIManager.h"


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
	InitTitleSceneUI();
}

/**************************************
終了処理
***************************************/
void TitleScene::Uninit()
{
	UninitTitleSceneUI();
}

/**************************************
更新処理
***************************************/
void TitleScene::Update(HWND hWnd)
{
	UpdateTitleSceneUI(hWnd);
}

/**************************************
描画処理
***************************************/
void TitleScene::Draw()
{
	DrawTitleSceneUI();
}