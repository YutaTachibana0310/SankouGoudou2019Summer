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
	entity->actor->ChangeAnimation(BossEnemyActor::AnimID::LargeDamage);
}

/**************************************
更新処理
***************************************/
int BossEnemyModel::BossLargeDamage::OnUpdate(BossEnemyModel * entity)
{
	cntFrame++;

	int result = BossEnemyModel::State::LargeDamage;

	if(cntFrame == 120)
	{
		result = RandomRange(0, 100) < 50 ? BossEnemyModel::State::HomingAttack : BossEnemyModel::State::RebarAttack;
	}

	return result;
}