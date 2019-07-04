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
#include "TrailCollider.h"

#include "EnemyController.h"


#include "Enemy.h"

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

Enemy *enemy[100];	//test用

/**************************************
初期化処理
***************************************/
void GameScene::Init()
{
	//インスタンス生成
	enemyController = new EnemyController();

	//UI初期化
	InitGameSceneUI();

	//☆ボタンの位置からワールド座標を計算
	LineTrailModel::CalcEdgePosition();

	//背景初期化
	InitSkyBox(0);
	InitBackGroundCity(0);
	InitBackGroundRoad();
	InitBackGroundField();

	//パーティクル初期化
	InitGameParticleManager(0);

	//プレイヤー初期化
	InitPlayerController();

	//サウンド初期化
	Sound::GetInstance()->Create();
#if 0
	//エネミーtest
	for (int i = 0; i < 50; i++)
	{
		enemy[i] = new EnemyStraight;
		enemy[i]->Init();
	}

	for (int i = 50; i < 100; i++)
	{
		enemy[i] = new EnemyChange;
		enemy[i]->Init();
	}

	for (int nCntEnemy = 0, i = 0; nCntEnemy < 50, i < 4; nCntEnemy++, i++)
	{
		if (!enemy[nCntEnemy]->active)
		{		
			enemy[nCntEnemy]->Set(D3DXVECTOR3(0.0f + 20.f*i, 50.0f, 15.0f), D3DXVECTOR3(0.0f + 20.f*i, 0.0f, 0.0f),200);
			
		}
	}

	for (int nCntEnemy = 50, i = 0; nCntEnemy < 100, i < 4; nCntEnemy++, i++)
	{
		if (!enemy[nCntEnemy]->active)
		{
			
			enemy[nCntEnemy]->SetVec(D3DXVECTOR3(0.0f + 20.f*i, 50.0f, 15.0f), D3DXVECTOR3(0.0f + 20.f*i, 20.0f, 0.0f), 200,50, D3DXVECTOR3 (3.0f,0.0f,-5.0f));
			
		}
	}
#endif

	//エネミー初期化
	enemyController->Init();

	//プロファイラにGameSceneを登録
	RegisterDebugTimer(GAMESCENE_LABEL);

}

/**************************************
終了処理
***************************************/
void GameScene::Uninit()
{
	//背景終了
	UninitSkyBox(0);
	UninitBackGroundCity(0);
	UninitBackGroundRoad();
	UninitBackGroundField();

	//パーティクル終了
	UninitGameParticleManager(0);

	//プレイヤー終了
	UninitPlayerController();

#if 0
	//エネミーtest
	for (int i = 0; i < 100; i++)
	{
		enemy[i]->Uninit();
	}
#endif

	//エネミー終了
	enemyController->Uninit();

	//UI終了
	UninitGameSceneUI();

	//インスタンス削除
	SAFE_DELETE(enemyController);
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

	//エネミーの更新
#if 0
	for (int i = 0; i < 100; i++)
	{
		enemy[i]->Update();
	}
#endif
	enemyController->Update();


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
	TrailCollider::UpdateCollision();
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
#if 0
	//エネミーtest
	for (int i = 0; i < 100; i++)
	{
		enemy[i]->Draw();
	}

#endif

	CountDebugTimer(GAMESCENE_LABEL, "DrawPlayer");

	//エネミーの描画
	enemyController->Draw();

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