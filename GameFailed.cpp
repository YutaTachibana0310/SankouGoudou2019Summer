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

/**************************************
グローバル変数
***************************************/

/**************************************
入場処理
***************************************/
void GameScene::GameFailed::OnStart(GameScene * entity)
{
	cntFrame = 0;
}

/**************************************
更新処理
***************************************/
int GameScene::GameFailed::OnUpdate(GameScene * entity)
{
	cntFrame++;

	float t = 1.0f * cntFrame / MonotoneDuration;
	MonotoneFilter::Instance()->SetPower(t);

	entity->UpdateWhole();
	entity->gameover->Update();

	if (cntFrame == TransitionDuration)
	{
		SceneChangeFlag(true, Scene::SceneResult);
	}

	return GameScene::State::Failed;
}
