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
#include "sound.h"

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

	titleSceneUIManager = new TitleSceneUIManager();

	titleSceneUIManager->Init();

}

/**************************************
終了処理
***************************************/
void TitleScene::Uninit()
{
	SAFE_DELETE(titleSceneUIManager);
	titleSceneUIManager->Uninit();
}

/**************************************
更新処理
***************************************/
void TitleScene::Update(HWND hWnd)
{
	titleSceneUIManager->Update(hWnd);
}

/**************************************
描画処理
***************************************/
void TitleScene::Draw()
{
	titleSceneUIManager->Draw();
}