//=====================================
//
//ゲームエンド処理[GameEnd.cpp]
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "GameEnd.h"

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

	//TODO：ここでゲーム終了テロップを再生する
}

/**************************************
更新処理
***************************************/
int GameEnd::OnUpdate(GameScene *entity)
{
	entity->cntFrame++;

	if (entity->cntFrame == GAMEEND_DURATION)
		return STATE_FINISHED;
	else
		return STATE_CONTINUOUS;
}