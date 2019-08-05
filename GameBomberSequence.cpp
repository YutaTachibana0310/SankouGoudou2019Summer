//=====================================
//
//ゲームボンバーシーケンス処理[GameBomberSequence.cpp]
//Author:GP12A332 21 立花雄太
//
//=====================================
#include "GameBomberSequence.h"
#include "PlayerObserver.h"
#include "GameParticleManager.h"

/**************************************
マクロ定義
***************************************/
#define GAMEBOMBERSEQUENCE_DURATION		(120)

/**************************************
入場処理
***************************************/
void GameBomberSequence::OnStart(GameScene* entity)
{
	entity->playerObserver->OnStartBomberSequence();
	cntFrame = 0;
}

/**************************************
更新処理
***************************************/
int GameBomberSequence::OnUpdate(GameScene* entity)
{
	cntFrame++;

	int result = GameScene::State::BombSequence;

	//プレイヤーのアニメーションだけさせる
	entity->playerObserver->Update();

	//パーティクルの更新
	entity->particleManager->Update();

	if (cntFrame == GAMEBOMBERSEQUENCE_DURATION)
	{
		entity->playerObserver->OnFinishBomberSequence();
		result = GameScene::State::Battle;
	}

	return result;
}