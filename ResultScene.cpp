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
#include "ResultPlayer.h"

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
	player = new ResultPlayer(false);

	InitResultSceneUI();

}

/**************************************
終了処理
***************************************/
void ResultScene::Uninit()
{
	UninitResultSceneUI();

	SAFE_DELETE(player);
}

/**************************************
更新処理
***************************************/
void ResultScene::Update(HWND hWnd)
{
	player->Update();
	UpdateResultSceneUI(hWnd);
}

/**************************************
描画処理
***************************************/
void ResultScene::Draw()
{
	player->Draw();
	DrawResultSceneUI();
}