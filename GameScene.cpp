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

#include "BackGroundCity.h"
#include "SkyBox.h"

#include "player.h"

/**************************************
マクロ定義
***************************************/

/**************************************
構造体定義
***************************************/

/**************************************
グローバル変数
***************************************/
class Player player;
/**************************************
初期化処理
***************************************/
void GameScene::Init()
{
	InitSkyBox(0);
	InitBackGroundCity(0);
	InitUIManager();

	player.Init();
}

/**************************************
終了処理
***************************************/
void GameScene::Uninit()
{
	UninitSkyBox(0);
	UninitBackGroundCity(0);

	UninitUIManager();

	player.Uninit();
}

/**************************************
更新処理
***************************************/
void GameScene::Update(HWND hWnd)
{
	UpdateSkyBox();
	UpdateBackGroundCity();
	UpdateUIManager(hWnd);
	player.Update();
}

/**************************************
描画処理
***************************************/
void GameScene::Draw()
{
	DrawSkyBox();

	DrawBackGroundCity();

	DrawUIManager();

	player.Draw();
}