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
#include "GameParticleManager.h"

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
	InitSkyBox(0);
	InitBackGroundCity(0);
	InitGameParticleManager(0);
	InitUIManager();
}

/**************************************
終了処理
***************************************/
void GameScene::Uninit()
{
	UninitSkyBox(0);
	UninitBackGroundCity(0);
	UninitGameParticleManager(0);
	UninitUIManager();

}

/**************************************
更新処理
***************************************/
void GameScene::Update(HWND hWnd)
{
	UpdateSkyBox();
	UpdateBackGroundCity();

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

	DrawGameParticleManager();

	DrawUIManager();

}