//=====================================
//
//ゲームエンド処理[GameEnd.cpp]
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "GameEnd.h"
#include "masktex.h"
#include "GameSceneUIManager.h"

/**************************************
マクロ定義
***************************************/
#define GAMEEND_DURATION	(60)

/**************************************
入場処理
***************************************/
void GameScene::GameEnd::OnStart(GameScene *entity)
{
	entity->cntFrame = 0;
	entity->gameSceneUIManager->SetStageClearTelop();
}

/**************************************
更新処理
***************************************/
int GameScene::GameEnd::OnUpdate(GameScene *entity)
{
	entity->cntFrame++;

	entity->UpdateWhole();

	const int Duration = 420;
	if (entity->cntFrame == Duration)
	{
		SceneChangeFlag(true, Scene::SceneResult);
	}

	return GameScene::State::End;
}