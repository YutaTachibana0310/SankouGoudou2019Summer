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
	entity->actor->ChangeAnimation(BossEnemyActor::AnimID::LargeDamage);
}

/**************************************
�X�V����
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