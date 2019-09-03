//=====================================
//
//�{�X�_���[�W�G�C�u������[BossDamageable.cpp]
//Author:GP12A332 21 ���ԗY��
//
//=====================================
#include "BossDamageable.h"

/**************************************
�}�N����`
***************************************/

/**************************************
���ꏈ��
***************************************/
void BossEnemyModel::BossDamageable::OnStart(BossEnemyModel* entity)
{
	cntFrame = 0;
	entity->SetCollider();
}

/**************************************
�X�V����
***************************************/
int BossEnemyModel::BossDamageable::OnUpdate(BossEnemyModel* entity)
{
	cntFrame++;

	int result = BossEnemyModel::State::Damageable;

	if (cntFrame == 360)
	{
		result = BossEnemyModel::State::Idle;
		entity->colliderController->DeleteAll();
	}

	return result;
}
