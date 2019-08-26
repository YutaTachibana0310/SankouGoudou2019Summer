//=====================================
//
//ゲームボンバーシーケンス処理[GameBomberSequence.cpp]
//Author:GP12A332 21 立花雄太
//
//=====================================
#include "GameBomberSequence.h"
#include "PlayerObserver.h"
#include "GameParticleManager.h"
#include "EnemyController.h"

#include <vector>

using namespace std;
/**************************************
マクロ定義
***************************************/
#define GAMEBOMBERSEQUENCE_DURATION		(120)
#define GAMEBOMBERSEQUENCE_LAUNCH_TIME	(80)

/**************************************
入場処理
***************************************/
void GameScene::GameBomberSequence::OnStart(GameScene* entity)
{
	entity->playerObserver->OnStartBomberSequence();
	entity->useDarkMask = true;
	cntFrame = 0;
}

/**************************************
更新処理
***************************************/
int GameScene::GameBomberSequence::OnUpdate(GameScene* entity)
{
	cntFrame++;

	int result = GameScene::State::BombSequence;

	//プレイヤーのアニメーションだけさせる
	entity->playerObserver->Update();

	//ボンバーのエフェクトだけ更新する
	entity->particleManager->UpdateBombParticle();

	//発射タイミングであればボンバー発射
	if (cntFrame == GAMEBOMBERSEQUENCE_LAUNCH_TIME)
	{
		list<Enemy*> targetList;
		entity->enemyController->GetEnemyList(targetList);
		entity->playerObserver->FirePlayerBomber(targetList);
	}

	//終了判定
	if (cntFrame == GAMEBOMBERSEQUENCE_DURATION)
	{
		entity->playerObserver->OnFinishBomberSequence();
		entity->enemyController->OnFinishBombSequence();
		entity->useDarkMask = false;

		result = entity->prevState;
	}

	return result;	
}