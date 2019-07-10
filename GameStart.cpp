//=====================================
//
//ゲームスタート処理[GameStart.cpp]
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "GameStart.h"

/**************************************
マクロ定義
***************************************/
#define GAMESTART_DURATION		(60)

/**************************************
入場処理
***************************************/
void GameStart::OnStart(GameScene *entity)
{
	entity->cntFrame = 0;

	//TODO:ここでゲームスタートのテロップを再生する

}

/**************************************
更新処理
***************************************/
int GameStart::OnUpdate(GameScene *entity)
{
	entity->cntFrame++;
	
	if (entity->cntFrame == GAMESTART_DURATION)
		return STATE_FINISHED;
	else
		return STATE_CONTINUOUS;
}