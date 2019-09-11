//=====================================
//
//ゲームエンド処理[GameEnd.cpp]
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "GameEnd.h"
#include "masktex.h"
#include "GameSceneUIManager.h"
#include "Framework\PlayerPrefs.h"

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
}

/**************************************
更新処理
***************************************/
int GameScene::GameEnd::OnUpdate(GameScene *entity)
{
	entity->cntFrame++;

	entity->UpdateWhole();

	const int TelopTiming = 360;
	const int Duration = 540;

	if (entity->cntFrame == TelopTiming)
	{
		entity->gameSceneUIManager->SetStageClearTelop();
	}

	if (entity->cntFrame == Duration)
	{
		PlayerPrefs::SaveBool("GameResult", true);
		SceneChangeFlag(true, Scene::SceneResult);
	}

	return GameScene::State::End;
}