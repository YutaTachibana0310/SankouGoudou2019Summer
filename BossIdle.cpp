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

	if (entity->cntLoop == 2)
	{
		entity->cntLoop = 0;
		entity->ChangeState(BossEnemyModel::State::Damageable);
	}
}

/**************************************
�X�V����
***************************************/
int BossEnemyModel::BossIdle::OnUpdate(BossEnemyModel * entity)
{
	cntFrame++;

	const int Duration = 60;
	int next = BossEnemyModel::State::Idle;

	if (cntFrame == Duration)
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
