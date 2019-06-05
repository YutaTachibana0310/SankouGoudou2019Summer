//=====================================
//
//ゲームシーン処理[GameScene.cpp]
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "GameScene.h"
#include "debugWindow.h"
#include "Game.h"
#include "UIManager.h"
#include "player.h"
#include "player_controller.h"
#include "InputController.h"

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
void GameScene::Init()
{
	InitUIManager();
	InitPlayer();
	InitPlayerController();
}

/**************************************
終了処理
***************************************/
void GameScene::Uninit()
{
	UninitUIManager();
	UninitPlayer();
}

/**************************************
更新処理
***************************************/
void GameScene::Update(HWND hWnd)
{
	UpdateUIManager(hWnd);
	UpdatePlayer();
	UpdatePlayerController(hWnd);

}

/**************************************
描画処理
***************************************/
void GameScene::Draw()
{
	DrawUIManager();
	DrawPlayer();
}