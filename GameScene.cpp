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

#include "sound.h"

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
	Sound::GetInstance()->Create();
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
	//サウンドの再生
	Sound::GetInstance()->SetPlaySound(1);
	Sound::GetInstance()->CangeSoundVolume(1,0.1f);
	//背景オブジェクトの更新
	UpdateSkyBox();
	UpdateBackGroundCity();
	UpdateBackGroundRoad();
	UpdateBackGroundField();

	//プレイヤーの更新
	UpdatePlayerController(hWnd);
	player.Update();

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

	//パーティクル描画
	DrawGameParticleManager();

	//ポストエフェクト描画
	PostEffectManager::Instance()->Draw();
	
	//UI描画
	DrawUI();
	DrawCursor();
}