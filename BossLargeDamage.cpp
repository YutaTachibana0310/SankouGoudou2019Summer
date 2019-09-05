//=====================================
//
//ボス大ダメージ処理[BossLargeDamage.cpp]
//Author:GP12A332 21 立花雄太
//
//=====================================
#include "BossLargeDamage.h"
#include "BossEnemyActor.h"

/**************************************
マクロ定義
***************************************/

/**************************************
入場処理
***************************************/
void BossEnemyModel::BossLargeDamage::OnStart(BossEnemyModel * entity)
{
	cntFrame = 0;

	entity->level++;

	if (entity->level == BossEnemyModel::Const::LevelMax)
		entity->ChangeState(BossEnemyModel::State::Defeat);
}

/**************************************
更新処理
***************************************/
int BossEnemyModel::BossLargeDamage::OnUpdate(BossEnemyModel * entity)
{
	cntFrame++;

	int result = BossEnemyModel::State::LargeDamage;
	const int AnimationChangeTiming = 15;
	const int FinishTiming = 150;

	if (cntFrame == AnimationChangeTiming)
	{
		entity->actor->ChangeAnimation(BossEnemyActor::AnimID::LargeDamage);
	}

	if(cntFrame == FinishTiming)
	{
		result = RandomRange(0, 100) < 50 ? BossEnemyModel::State::HomingAttack : BossEnemyModel::State::RebarAttack;
	}

	return result;
}