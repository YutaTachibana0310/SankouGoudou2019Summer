//=====================================
//
//テンプレート処理[GameBossStart.cpp]
//Author:GP12A332 21 立花雄太
//
//=====================================
#include "GameBossStart.h"
#include "BossUIManager.h"

/**************************************
マクロ定義
***************************************/

/**************************************
入場処理
***************************************/
void GameScene::GameBossStart::OnStart(GameScene * entity)
{
	entity->cntFrame = 0;
	entity->bossUI->SetWarning();
}

/**************************************
更新処理
***************************************/
int GameScene::GameBossStart::OnUpdate(GameScene * entity)
{
	int result = GameScene::State::BossStart;

	entity->UpdateWhole();

	entity->cntFrame++;

	const int StateDuration = 300;
	if (entity->cntFrame == StateDuration)
	{
		result = GameScene::State::BossBattle;
	}

	return result;
}
