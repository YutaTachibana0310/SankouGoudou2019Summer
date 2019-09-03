//=====================================
//
//リザルトシーン処理[ResultScene.cpp]
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "ResultScene.h"
#include "debugWindow.h"
#include "Game.h"
#include "ResultSceneUIManager.h"


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
void ResultScene::Init()
{
	resultSceneUIManager = new ResultSceneUIManager;

	resultSceneUIManager->Init();
}

/**************************************
終了処理
***************************************/
void ResultScene::Uninit()
{
	SAFE_DELETE(resultSceneUIManager);
	resultSceneUIManager->Uninit();
}

/**************************************
更新処理
***************************************/
void ResultScene::Update(HWND hWnd)
{
	resultSceneUIManager->Update(hWnd);
}

/**************************************
描画処理
***************************************/
void ResultScene::Draw()
{
	resultSceneUIManager->Draw();
}