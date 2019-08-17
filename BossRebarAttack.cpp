//=====================================
//
//�{�X�S�؃A�^�b�N����[BossRebarAttack.cpp]
//Author:GP12A332 21 ���ԗY��
//
//=====================================
#include "BossRebarAttack.h"
#include "BossEnemyActor.h"

/**************************************
�}�N����`
***************************************/

/**************************************
���ꏈ��
***************************************/
void BossEnemyModel::BossRebarAttack::OnStart(BossEnemyModel* entity)
{
	cntFrame = 0;

	//�A�j���[�V�����J��
	entity->actor->ChangeAnimation(BossEnemyActor::AnimID::Attack02);
}

/**************************************
�X�V����
***************************************/
int BossEnemyModel::BossRebarAttack::OnUpdate(BossEnemyModel* entity)
{
	const int RebarSetTime = 60;
	const int RebarMoveDuration = 85;
	const int RebarAttackTime = 200;
	const int RebarThrowDuration = 180;

	cntFrame++;

	if (cntFrame == RebarSetTime)
	{
		entity->SetRebar();
	}

	if (cntFrame == RebarAttackTime)
	{
		entity->ThrowRebar();
	}

	return 0;
}
