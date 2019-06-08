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
#include "PlayerController.h"
#include "InputController.h"

#include "BackGroundCity.h"
#include "BackGroundRoad.h"
#include "BackGroundField.h"
#include "SkyBox.h"
#include "GameParticleManager.h"

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

	InitBackGroundRoad();
	InitBackGroundField();

	InitGameParticleManager(0);

	InitUIManager();

	InitPlayerController();
	player.Init();
}

/**************************************
終了処理
***************************************/
void GameScene::Uninit()
{
	UninitSkyBox(0);
	UninitBackGroundCity(0);

	UninitBackGroundRoad();
	UninitBackGroundField();

	UninitGameParticleManager(0);

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

	UpdateBackGroundRoad();
	UpdateBackGroundField();

	UpdatePlayerController(hWnd);
	player.Update();

	UpdateGameParticleManager();

	UpdateUIManager(hWnd);

}

/**************************************
描画処理
***************************************/
void GameScene::Draw()
{
	DrawSkyBox();

	DrawBackGroundCity();
	DrawBackGroundRoad();
	DrawBackGroundField();

	player.Draw();

	DrawGameParticleManager();

	DrawUIManager();

}