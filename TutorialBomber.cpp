//=====================================
//
//TutorialBomber.cpp
//機能:
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "TutorialBomber.h"
#include "TutorialEnemyController.h"
#include "PlayerObserver.h"
#include "GameParticleManager.h"

/**************************************
グローバル変数
***************************************/
#define TUTORIALBOMBERSEQUENCE_DURATION		(120)
#define TUTORIALBOMBERSEQUENCE_LAUNCH_TIME	(80)

/**************************************
入場処理
***************************************/
void TutorialScene::TutorialBomber::OnStart(TutorialScene * entity)
{
	entity->playerObserver->OnStartBomberSequence();
	entity->useDarkMask = true;
	cntFrame = 0;
}


/**************************************
更新処理
***************************************/
int TutorialScene::TutorialBomber::OnUpdate(TutorialScene * entity)
{
	int result = TutorialScene::State::Bomber;

	cntFrame++;

	//プレイヤーのアニメーションだけさせる
	entity->playerObserver->Update();

	//ボンバーのエフェクトだけ更新する
	GameParticleManager::Instance()->UpdateBombParticle();

	//発射タイミングであればボンバー発射
	if (cntFrame == TUTORIALBOMBERSEQUENCE_LAUNCH_TIME)
	{
		list<shared_ptr<Enemy>> targetList;
		entity->enemyController->GetEnemyList(targetList);
		entity->playerObserver->FirePlayerBomber(targetList);
	}

	////終了判定
	if (cntFrame == TUTORIALBOMBERSEQUENCE_DURATION)
	{
		entity->playerObserver->OnFinishBomberSequence();
		entity->useDarkMask = false;

		result = State::Idle;
	}

	return result;
}
