//=====================================
//
//ゲームスタート処理[GameStart.cpp]
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "GameStart.h"
#include "GameSceneUIManager.h"

/**************************************
マクロ定義
***************************************/
#define GAMESTART_DURATION		(60)

/**************************************
入場処理
***************************************/
void GameScene::GameStart::OnStart(GameScene *entity)
{
	entity->cntFrame = 0;

	entity->gameSceneUIManager->SetBattleStartTelop();
}

/**************************************
更新処理
***************************************/
int GameScene::GameStart::OnUpdate(GameScene *entity)
{
	entity->cntFrame++;

	entity->UpdateWhole();
	
	if (entity->cntFrame == GAMESTART_DURATION)
		return GameScene::State::Battle;
	else
		return GameScene::State::Start;
}