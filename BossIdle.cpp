//=====================================
//
//ボスアイドル処理[BossIdle.cpp]
//Author:GP12A332 21 立花雄太
//
//=====================================
#include "BossIdle.h"
#include "BossEnemyActor.h"

/**************************************
マクロ定義
***************************************/

/**************************************
入場処理
***************************************/
void BossEnemyModel::BossIdle::OnStart(BossEnemyModel * entity)
{
	entity->actor->ChangeAnimation(BossEnemyActor::AnimID::Idle);
	cntFrame = 0;

	if (entity->cntLoop == 3)
	{
		entity->cntLoop = 0;
		entity->ChangeState(BossEnemyModel::State::Damageable);
	}
}

/**************************************
更新処理
***************************************/
int BossEnemyModel::BossIdle::OnUpdate(BossEnemyModel * entity)
{
	cntFrame++;

	int next = BossEnemyModel::State::Idle;

	if (cntFrame == 120)
	{
		if (entity->prevState == BossEnemyModel::State::HomingAttack)
			next = BossEnemyModel::State::RebarAttack;

		else if (entity->prevState == BossEnemyModel::State::RebarAttack)
			next = BossEnemyModel::State::HomingAttack;

		else
			next = RandomRange(0, 100) < 50 ? BossEnemyModel::State::RebarAttack : BossEnemyModel::State::HomingAttack;
	}

	return next;
}
