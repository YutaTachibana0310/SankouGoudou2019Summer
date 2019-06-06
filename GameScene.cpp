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

#include "EnemyController.h"
/**************************************
マクロ定義
***************************************/

/**************************************
構造体定義
***************************************/

/**************************************
グローバル変数
***************************************/
static Enemy* enemy[ENMEY_MAX];
/**************************************
初期化処理
***************************************/
void GameScene::Init()
{
	InitSkyBox(0);
	InitBackGroundCity(0);
	InitUIManager();

	//エネミーの初期化
	for (int i = 0; i <= ENMEY_MAX; i++)
	{
		enemy[i] = new EnemyStraight;
		enemy[i]->Init();
	}
}

/**************************************
終了処理
***************************************/
void GameScene::Uninit()
{
	UninitSkyBox(0);
	UninitBackGroundCity(0);

	UninitUIManager();

	//エネミーの終了処理
	for (int i = 0; i <= ENMEY_MAX; i++)
	{
		enemy[i]->Uninit(enemy[i]);
	}

}

/**************************************
更新処理
***************************************/
void GameScene::Update(HWND hWnd)
{
	UpdateSkyBox();
	UpdateBackGroundCity();
	UpdateUIManager(hWnd);

	//エネミーの更新処理
	for (int i = 0; i <= ENMEY_MAX; i++)
	{
		enemy[i]->Update(hWnd);
	}

}

/**************************************
描画処理
***************************************/
void GameScene::Draw()
{
	DrawSkyBox();

	DrawBackGroundCity();

	DrawUIManager();

	//エネミーの描画処理
	for (int i = 0; i <= ENMEY_MAX; i++)
	{
		enemy[i]->Draw();
	}
	BeginDebugWindow("count");
	DebugText("objNum:%d", Enemy::objNum);
	EndDebugWindow("count");
}