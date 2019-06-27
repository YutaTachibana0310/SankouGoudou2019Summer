//=====================================
//
//ゲームシーン処理[GameScene.cpp]
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "GameScene.h"
#include "debugWindow.h"
#include "Game.h"
#include "LineTrailModel.h"
#include "PostEffectManager.h"
#include "debugWindow.h"
#include "debugTimer.h"

#include "GameSceneUIManager.h"
#include "player.h"
#include "PlayerController.h"
#include "InputController.h"

#include "BackGroundCity.h"
#include "BackGroundRoad.h"
#include "BackGroundField.h"
#include "SkyBox.h"
#include "GameParticleManager.h"

#include "sound.h"
#include "CollisionManager.h"

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

/**************************************
初期化処理
***************************************/
void GameScene::Init()
{
	InitGameSceneUI();
	LineTrailModel::CalcEdgePosition();

	InitSkyBox(0);
	InitBackGroundCity(0);

	InitBackGroundRoad();
	InitBackGroundField();

	InitGameParticleManager(0);

	InitPlayerController();
	Sound::GetInstance()->Create();


	RegisterDebugTimer(GAMESCENE_LABEL);
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

	UninitPlayerController();

	UninitGameSceneUI();
}

/**************************************
更新処理
***************************************/
void GameScene::Update(HWND hWnd)
{
	//サウンド再生(テスト）
	InputSound();

	//背景オブジェクトの更新
	CountDebugTimer(GAMESCENE_LABEL, "UpdateBG");
	UpdateSkyBox();
	UpdateBackGroundCity();
	UpdateBackGroundRoad();
	UpdateBackGroundField();
	CountDebugTimer(GAMESCENE_LABEL, "UpdateBG");

	//プレイヤーの更新
	CountDebugTimer(GAMESCENE_LABEL, "UpdatePlayer");
	UpdatePlayerController(hWnd);
	CountDebugTimer(GAMESCENE_LABEL, "UpdatePlayer");

	//パーティクルの更新
	CountDebugTimer(GAMESCENE_LABEL, "UpdateParticle");
	UpdateGameParticleManager();
	CountDebugTimer(GAMESCENE_LABEL, "UpdateParticle");

	//UIの更新
	CountDebugTimer(GAMESCENE_LABEL, "UpdateUI");
	UpdateGameSceneUI(hWnd);
	CountDebugTimer(GAMESCENE_LABEL, "UpdateUI");

	//ポストエフェクトの更新
	PostEffectManager::Instance()->Update();

	//衝突判定
	UpdateCollisionManager();
}

/**************************************
描画処理
***************************************/
void GameScene::Draw()
{
	//背景の描画
	CountDebugTimer(GAMESCENE_LABEL, "DrawBG");
	DrawSkyBox();
	DrawBackGroundCity();
	DrawBackGroundRoad();
	DrawBackGroundField();
	CountDebugTimer(GAMESCENE_LABEL, "DrawBG");

	//プレイヤーの描画
	CountDebugTimer(GAMESCENE_LABEL, "DrawPlayer");
	DrawPlayerController();
	CountDebugTimer(GAMESCENE_LABEL, "DrawPlayer");

	//ポストエフェクト描画
	CountDebugTimer(GAMESCENE_LABEL, "DrawpostEffect");
	PostEffectManager::Instance()->Draw();
	CountDebugTimer(GAMESCENE_LABEL, "DrawpostEffect");

	//パーティクル描画
	CountDebugTimer(GAMESCENE_LABEL, "DrawParticle");
	DrawGameParticleManager();
	CountDebugTimer(GAMESCENE_LABEL, "DrawParticle");

	//UI描画
	DrawGameSceneUI();

	DrawDebugTimer(GAMESCENE_LABEL);
}