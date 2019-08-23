//=====================================
//
//�{�X���j����[BossDefeat.cpp]
//Author:GP12A332 21 ���ԗY��
//
//=====================================
#include "BossDefeat.h"
#include "BossEnemyActor.h"

/**************************************
�}�N����`
***************************************/

/**************************************
�N���X��`
***************************************/
void BossEnemyModel::BossDefeat::OnStart(BossEnemyModel* entity)
{
	cntFrame = 0;
	entity->Explode();
}

/**************************************
�O���[�o���ϐ�
***************************************/
int BossEnemyModel::BossDefeat::OnUpdate(BossEnemyModel* entity)
{
	cntFrame++;

	if(cntFrame == 10)
		entity->actor->ChangeAnimation(BossEnemyActor::AnimID::Defeat);

	return BossEnemyModel::State::Defeat;
}
