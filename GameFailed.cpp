//=====================================
//
//GameFailed.cpp
//機能:ゲームオーバーステート
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "GameFailed.h"
#include "PostEffect\MonotoneFilter.h"
#include "PostEffectManager.h"
#include "GameOver.h"
#include "masktex.h"
#include "PlayerObserver.h"

/**************************************
グローバル変数
***************************************/

/**************************************
入場処理
***************************************/
void GameScene::GameFailed::OnStart(GameScene * entity)
{
	cntFrame = 0;
	entity->playerObserver->OnGameOver();
}

/**************************************
更新処理
***************************************/
int GameScene::GameFailed::OnUpdate(GameScene * entity)
{
	cntFrame++;

	//モノトーンフィルタの強さを計算
	float t = 1.0f * cntFrame / MonotoneDuration;
	MonotoneFilter::Instance()->SetPower(t);

	//ゲーム全体とGAMEOVER表示を更新
	entity->UpdateWhole();
	entity->gameover->Update();

	//指定時間経過していたらシーン遷移
	if (cntFrame == TransitionDuration)
	{
		SceneChangeFlag(true, Scene::SceneResult);
	}

	return GameScene::State::Failed;
}
