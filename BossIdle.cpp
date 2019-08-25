//=====================================
//
//�{�X�A�C�h������[BossIdle.cpp]
//Author:GP12A332 21 ���ԗY��
//
//=====================================
#include "BossIdle.h"
#include "BossEnemyActor.h"

/**************************************
�}�N����`
***************************************/

/**************************************
���ꏈ��
***************************************/
void BossEnemyModel::BossIdle::OnStart(BossEnemyModel * entity)
{
	entity->actor->ChangeAnimation(BossEnemyActor::AnimID::Idle);
	cntFrame = 0;
}

/**************************************
�X�V����
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
