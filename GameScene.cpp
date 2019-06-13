//=====================================
//
//ゲームシーン処理[GameScene.cpp]
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "GameScene.h"
#include "debugWindow.h"
#include "Game.h"
#include "PostEffectManager.h"
#include "debugWindow.h"
#include "debugTimer.h"

#include "UIManager.h"
#include "cursor.h"
#include "player.h"
#include "PlayerController.h"
#include "InputController.h"

#include "BackGroundCity.h"
#include "BackGroundRoad.h"
#include "BackGroundField.h"
#include "SkyBox.h"
#include "GameParticleManager.h"

#include "player.h"
#include "PlayerBullet.h"

PlayerBullet *tmp;
/**************************************
マクロ定義
***************************************/
#define GAMESCENE_LABEL ("GameScene")

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

	InitUI();

	InitPlayerController();
	player.Init();
	InitCursor();

	tmp = new PlayerBullet();
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

	UninitUI();

	player.Uninit();
	UninitCursor();
}

/**************************************
更新処理
***************************************/
void GameScene::Update(HWND hWnd)
{
	BeginDebugWindow("Bullet");
	if (DebugButton("Fire"))
	{
		tmp->Set(D3DXVECTOR3(-100.0f, RandomRangef(-100.0f, 100.0f), 0.0f), D3DXVECTOR3(100.0f, RandomRangef(-100.0f, 100.0f), 0.0f));
	}
	EndDebugWindow("Bullet");

	//背景オブジェクトの更新
	UpdateSkyBox();
	UpdateBackGroundCity();
	UpdateBackGroundRoad();
	UpdateBackGroundField();

	//プレイヤーの更新
	UpdatePlayerController(hWnd);
	player.Update();
	tmp->Update();

	//パーティクルの更新
	UpdateGameParticleManager();

	//UIの更新
	UpdateUI(hWnd);
	UpdateCursor(hWnd);

	//ポストエフェクトの更新
	PostEffectManager::Instance()->Update();
}

/**************************************
描画処理
***************************************/
void GameScene::Draw()
{
	//背景の描画
	DrawSkyBox();
	DrawBackGroundCity();
	DrawBackGroundRoad();
	DrawBackGroundField();

	//プレイヤーの描画
	player.Draw();
	tmp->Draw();

	//パーティクル描画
	DrawGameParticleManager();

	//ポストエフェクト描画
	//PostEffectManager::Instance()->Draw();
	
	//UI描画
	DrawUI();
	DrawCursor();
}