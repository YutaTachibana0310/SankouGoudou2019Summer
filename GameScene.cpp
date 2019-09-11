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
#include "BackGroundController.h"
#include "BackGroundRoad.h"
#include "BackGroundField.h"
#include "GameParticleManager.h"
#include "sound.h"
#include "EnemyController.h"
#include "masktex.h"
#include "ScoreManager.h"
#include "PostEffect\SpeedBlurController.h"
#include "BossController.h"
#include "BossUIManager.h"
#include "PostEffect\MonotoneFilter.h"
#include "GameOver.h"

#include "GameStart.h"
#include "GameBattle.h"
#include "GameEnd.h"
#include "GameBomberSequence.h"
#include "GameBossBattle.h"
#include "GameBossStart.h"
#include "GameBossBombSequence.h"
#include "GameFailed.h"

#include "RebarOb.h"
#include <functional>

#include "SoundGameScene.h"

using namespace std;

/**************************************
マクロ定義
***************************************/
#define GAMESCENE_LABEL			("GameScene")
#define COMBOEFFECT_PERIOD		(25)			//このコンボおきに演出が発生する

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
	fsm[State::BombSequence] = new GameBomberSequence();
	fsm[State::BossBattle] = new GameBossBattle();
	fsm[State::BossStart] = new GameBossStart();
	fsm[State::BossBombSequence] = new GameBossBombSequence();
	fsm[State::Failed] = new GameFailed();

	//暗転用ポリゴン作成
	darkMask = new Polygon2D();
	darkMask->SetSize((float)SCREEN_WIDTH, (float)SCREEN_HEIGHT);
	darkMask->SetColor(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.5f));
	useDarkMask = false;

	gameSceneUIManager = new GameSceneUIManager();

	//UI初期化
	gameSceneUIManager->Init();

	//☆ボタンの位置からワールド座標を計算
	std::vector<D3DXVECTOR3> starPositionContainer;
	gameSceneUIManager->GetStarPosition(starPositionContainer);
	LineTrailModel::CalcEdgePosition(starPositionContainer);

	//インスタンス生成
	enemyController = new EnemyController();
	particleManager = GameParticleManager::Instance();
	playerObserver = new PlayerObserver();
	bgController = new BackGroundController();
	bossUI = new BossUImanager();
	bossController = new BossController(playerObserver->GetPlayerTransform(), *bossUI);
	gameover = new GameOver();

	SetPlayerObserverAdr(playerObserver);

	//背景初期化
	InitBackGroundRoad();
	InitBackGroundField();
	bgController->Init();

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
	SoundGameScene::SetScene(currentState);

	//コールバック設定
	currentCombo = 0;
	SetCallbackClearCombo([&]()
	{
		this->OnClearCombo();
	});

	SetCallbackAddCombo([&](int n)
	{
		this->OnAddCombo(n);
	});
	SetGameScneeUIManagerInstance(gameSceneUIManager);

	//インプットコントローラにUImanagerのインスタンスを渡す
	SetInstanceUIManager(gameSceneUIManager);

	//スコア初期化
	SetCurrentGameScore(0);
	SetCurrentCombo(0);
}

/**************************************
終了処理
***************************************/
void GameScene::Uninit()
{
	//背景終了
	UninitBackGroundRoad();
	UninitBackGroundField();
	bgController->Uninit();

	//プレイヤー終了
	playerObserver->Uninit();

	//エネミー終了
	enemyController->Uninit();

	//UI終了
	gameSceneUIManager->Uninit();

	//スコアマネージャクリア
	ClearScoreManager();

	//インスタンス削除
	SAFE_DELETE(gameSceneUIManager);
	SAFE_DELETE(enemyController);
	SAFE_DELETE(playerObserver);
	SAFE_DELETE(bgController);
	SAFE_DELETE(darkMask);
	SAFE_DELETE(bossController);
	SAFE_DELETE(bossUI);

	//パーティクル終了
	particleManager->Uninit();

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

	//ステート更新処理
	int result = state->OnUpdate(this);

	if (result != currentState)
		ChangeState(result);
	SoundGameScene::SetScene(result);

	//UIの更新
	CountDebugTimer(GAMESCENE_LABEL, "UpdateUI");
	gameSceneUIManager->SetHPGuage(playerObserver->GetHpPercent());
	gameSceneUIManager->SetBomberStock(playerObserver->GetBomberStockNum(), playerObserver->IsBomberCharging());
	gameSceneUIManager->Update(hWnd);
	bossUI->Update();
	CountDebugTimer(GAMESCENE_LABEL, "UpdateUI");

	BeginDebugWindow("Console");
	if (DebugButton("AddCombo")) SetAddCombo(1);
	if (DebugButton("ResetCombo")) ClearCombo();
	EndDebugWindow("");
}

/**************************************
描画処理
***************************************/
void GameScene::Draw()
{
	//背景の描画
	CountDebugTimer(GAMESCENE_LABEL, "DrawBG");
	//DrawBackGroundRoad();
	//DrawBackGroundField();
	bgController->Draw();
	CountDebugTimer(GAMESCENE_LABEL, "DrawBG");

	//暗転用ポリゴンの描画
	if (useDarkMask)
	{
		LPDIRECT3DDEVICE9 pDevice = GetDevice();
		pDevice->SetRenderState(D3DRS_ZWRITEENABLE, false);

		darkMask->Draw();

		pDevice->SetRenderState(D3DRS_ZWRITEENABLE, true);
	}

	//エネミーの描画
	enemyController->Draw();
	enemyController->DrawGuide();

	//ボスの描画
	bossController->Draw();

	//プレイヤーの描画
	CountDebugTimer(GAMESCENE_LABEL, "DrawPlayer");
	playerObserver->Draw();
	CountDebugTimer(GAMESCENE_LABEL, "DrawPlayer");

	//パーティクル描画
	CountDebugTimer(GAMESCENE_LABEL, "DrawParticle");
	particleManager->Draw();
	CountDebugTimer(GAMESCENE_LABEL, "DrawParticle");

	//ポストエフェクト描画
	CountDebugTimer(GAMESCENE_LABEL, "DrawpostEffect");
	PostEffectManager::Instance()->Draw();
	CountDebugTimer(GAMESCENE_LABEL, "DrawpostEffect");

	//UI描画
	gameSceneUIManager->Draw();
	bossUI->Draw();
	playerObserver->DrawInputGuide();

	//ゲームオーバー時のモノトーンフィルタ描画
	if (!playerObserver->IsAlive())
	{
		MonotoneFilter::Instance()->Draw();
		gameover->Draw();
	}

	DrawDebugTimer(GAMESCENE_LABEL);
}

/**************************************
ステート遷移処理
***************************************/
void GameScene::ChangeState(int next)
{
	if (next < 0 || next >= State::StateMax)
		return;

	prevState = currentState;
	currentState = (State)next;
	state = fsm[currentState];
	state->OnStart(this);
	SoundGameScene::SetScene(currentState);

}

/**************************************
全体更新処理
***************************************/
void GameScene::UpdateWhole()
{
	//背景オブジェクトの更新
	CountDebugTimer(GAMESCENE_LABEL, "UpdateBG");
	UpdateBackGroundRoad();
	UpdateBackGroundField();
	bgController->Update();
	CountDebugTimer(GAMESCENE_LABEL, "UpdateBG");

	//エネミーの更新
	enemyController->Update();

	//ボスの更新
	bossController->Update();

	//プレイヤーの更新
	CountDebugTimer(GAMESCENE_LABEL, "UpdatePlayer");
	playerObserver->Update();
	CountDebugTimer(GAMESCENE_LABEL, "UpdatePlayer");

	//パーティクルの更新
	CountDebugTimer(GAMESCENE_LABEL, "UpdateParticle");
	particleManager->Update();
	CountDebugTimer(GAMESCENE_LABEL, "UpdateParticle");

	//ポストエフェクトの更新
	PostEffectManager::Instance()->Update();
}

/**************************************
全体描画処理
***************************************/
void GameScene::DrawWhole()
{

}

/**************************************
コンボ加算時演出
***************************************/
void GameScene::OnAddCombo(int n)
{
	static const float AddPower = 10.0f;
	static const float AddSpeed = -50.0f;

	currentCombo += n;

	if (currentCombo % COMBOEFFECT_PERIOD != 0)
		return;

	SpeedBlurController::Instance()->AddPower(AddPower);
	bgController->AddScrollSpeed(AddSpeed);
	playerObserver->OnStartAccel();
}

/**************************************
コンボクリア時演出
***************************************/
void GameScene::OnClearCombo()
{
	static const float InitPower = 0.0f;

	currentCombo = 0;

	SpeedBlurController::Instance()->SetPower(InitPower);
	bgController->InitScroolSpeed();
}

/**************************************
ボンバー発射判定
***************************************/
bool GameScene::ShouldFireBomber()
{
	return playerObserver->ShouldFireBomber() && enemyController->ExistsAcitveEnemy();
}

/**************************************
ボス戦時
***************************************/
bool GameScene::ShouldFireBomberOnBossBattle()
{
	//TODO : ボス撃墜後にボンバーを発射できないようにする
	return  playerObserver->ShouldFireBomber();
}
