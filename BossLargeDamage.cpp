//=====================================
//
//�{�X��_���[�W����[BossLargeDamage.cpp]
//Author:GP12A332 21 ���ԗY��
//
//=====================================
#include "BossLargeDamage.h"
#include "BossEnemyActor.h"

/**************************************
�}�N����`
***************************************/

/**************************************
���ꏈ��
***************************************/
void BossEnemyModel::BossLargeDamage::OnStart(BossEnemyModel * entity)
{
	cntFrame = 0;

	entity->level++;

	if (entity->level == 3)
		entity->ChangeState(BossEnemyModel::State::Defeat);
}

/**************************************
�X�V����
***************************************/
int BossEnemyModel::BossLargeDamage::OnUpdate(BossEnemyModel * entity)
{
	cntFrame++;

	int result = BossEnemyModel::State::LargeDamage;

	if (cntFrame == 15)
	{
		entity->actor->ChangeAnimation(BossEnemyActor::AnimID::LargeDamage);
	}

	if(cntFrame == 150)
	{
		result = RandomRange(0, 100) < 50 ? BossEnemyModel::State::HomingAttack : BossEnemyModel::State::RebarAttack;
	}

	return result;
}