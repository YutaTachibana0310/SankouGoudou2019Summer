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
#include "PlayerController.h"
#include "PlayerObserver.h"
#include "InputController.h"
#include "BackGroundCity.h"
#include "BackGroundRoad.h"
#include "BackGroundField.h"
#include "SkyBox.h"
#include "GameParticleManager.h"
#include "sound.h"
#include "EnemyController.h"
#include "masktex.h"

#include "GameStart.h"
#include "GameBattle.h"
#include "GameEnd.h"

using namespace std;

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
	//ステートマシン作成
	fsm[State::Start] = new GameStart();
	fsm[State::Battle] = new GameBattle();
	fsm[State::End] = new GameEnd();

	//UI初期化
	InitGameSceneUI();

	//☆ボタンの位置からワールド座標を計算
	LineTrailModel::CalcEdgePosition();

	//インスタンス生成
	enemyController = new EnemyController();
	particleManager = GameParticleManager::Instance();
	playerObserver = new PlayerObserver();

	SetPlayerObserverAdr(playerObserver);

	//背景初期化
	InitSkyBox(0);
	InitBackGroundCity(0);
	InitBackGroundRoad();
	InitBackGroundField();

	//パーティクル初期化
	particleManager->Init();

	//プレイヤー初期化
	playerObserver->Init();

	//サウンド初期化
	Sound::GetInstance()->Create();

	//エネミー初期化
	enemyController->Init();

	//プロファイラにGameSceneを登録
	RegisterDebugTimer(GAMESCENE_LABEL);

	//ステート初期化
	currentState = State::Start;
	state = fsm[currentState];
	state->OnStart(this);

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
	particleManager->Uninit();

	//プレイヤー終了
	playerObserver->Uninit();

	//エネミー終了
	enemyController->Uninit();

	//UI終了
	UninitGameSceneUI();

	//インスタンス削除
	SAFE_DELETE(enemyController);
	SAFE_DELETE(playerObserver);

	//ステートマシン削除
	for (auto& pair : fsm)
	{
		SAFE_DELETE(pair.second);
	}
	fsm.clear();
}

/**************************************
更新処理
***************************************/
void GameScene::Update(HWND hWnd)
{
	//サウンド再生(テスト）
	InputSound();

	//ステート更新処理
	int result = state->OnUpdate(this);

	//背景オブジェクトの更新
	CountDebugTimer(GAMESCENE_LABEL, "UpdateBG");
	UpdateSkyBox();
	UpdateBackGroundCity();
	UpdateBackGroundRoad();
	UpdateBackGroundField();
	CountDebugTimer(GAMESCENE_LABEL, "UpdateBG");

	//プレイヤーの更新
	CountDebugTimer(GAMESCENE_LABEL, "UpdatePlayer");
	playerObserver->Update();
	CountDebugTimer(GAMESCENE_LABEL, "UpdatePlayer");

	//エネミーの更新
	enemyController->Update();

	//パーティクルの更新
	CountDebugTimer(GAMESCENE_LABEL, "UpdateParticle");
	particleManager->Update();
	CountDebugTimer(GAMESCENE_LABEL, "UpdateParticle");

	//UIの更新
	CountDebugTimer(GAMESCENE_LABEL, "UpdateUI");
	UpdateGameSceneUI(hWnd);
	CountDebugTimer(GAMESCENE_LABEL, "UpdateUI");

	//ポストエフェクトの更新
	PostEffectManager::Instance()->Update();

	//遷移処理
	if (result != STATE_CONTINUOUS)
		ChangeState(result);
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
	playerObserver->Draw();
	CountDebugTimer(GAMESCENE_LABEL, "DrawPlayer");

	//エネミーの描画
	enemyController->Draw();

	//ポストエフェクト描画
	CountDebugTimer(GAMESCENE_LABEL, "DrawpostEffect");
	PostEffectManager::Instance()->Draw();
	CountDebugTimer(GAMESCENE_LABEL, "DrawpostEffect");

	//パーティクル描画
	CountDebugTimer(GAMESCENE_LABEL, "DrawParticle");
	particleManager->Draw();
	CountDebugTimer(GAMESCENE_LABEL, "DrawParticle");

	//UI描画
	DrawGameSceneUI();

	DrawDebugTimer(GAMESCENE_LABEL);
}

/**************************************
ステート遷移処理
***************************************/
void GameScene::ChangeState(int resultUpdate)
{
	switch (currentState)
	{
	case GameScene::State::Idle:

		break;

	case GameScene::State::Start:
		currentState = State::Battle;
		state = fsm[currentState];
		state->OnStart(this);
		break;

	case GameScene::State::Battle:
		currentState = State::End;
		Sound::GetInstance()->playsound = true;
		state = fsm[currentState];
		state->OnStart(this);
		break;

	case GameScene::State::End:
		SceneChangeFlag(true, Scene::SceneResult);
		break;

	default:
		break;
	}
}
