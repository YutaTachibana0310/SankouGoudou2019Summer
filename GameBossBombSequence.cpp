//=====================================
//
//ボスバトルボンバーシーケンス処理[GameBossBombSequence.cpp]
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "GameBossBombSequence.h"
#include "PlayerObserver.h"
#include "GameParticleManager.h"
#include "BossController.h"

/**************************************
グローバル変数
***************************************/

/**************************************
入場処理
***************************************/
void GameScene::GameBossBombSequence::OnStart(GameScene * entity)
{
	entity->playerObserver->OnStartBomberSequence();
	entity->useDarkMask = true;
	cntFrame = 0;
}

/**************************************
更新処理
***************************************/
int GameScene::GameBossBombSequence::OnUpdate(GameScene * entity)
{
	const int BomberFireTiming = 80;
	const int StateDuration = 120;

	cntFrame++;

	int result = GameScene::State::BossBombSequence;

	//プレイヤーのアニメーションだけさせる
	entity->playerObserver->Update();
	
	//ボンバーのエフェクトだけ更新する
	entity->particleManager->UpdateBombParticle();

	//発射タイミングであれば発射
	if (entity->cntFrame == BomberFireTiming)
	{

	}

	//終了判定
	if (cntFrame == StateDuration)
	{
		entity->playerObserver->OnFinishBomberSequence();
		
		entity->useDarkMask = false;

		result = GameScene::State::BossBattle;
	}

	return result;
}
