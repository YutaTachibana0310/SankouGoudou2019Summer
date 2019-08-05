//=====================================
//
//ゲームエンド処理[GameEnd.cpp]
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "GameEnd.h"
#include "masktex.h"

/**************************************
マクロ定義
***************************************/
#define GAMEEND_DURATION	(60)

/**************************************
入場処理
***************************************/
void GameEnd::OnStart(GameScene *entity)
{
	entity->cntFrame = 0;
	SceneChangeFlag(true, Scene::SceneResult);

	//TODO：ここでゲーム終了テロップを再生する
}

/**************************************
更新処理
***************************************/
int GameEnd::OnUpdate(GameScene *entity)
{
	entity->cntFrame++;

	entity->UpdateWhole();

	return GameScene::State::End;
}