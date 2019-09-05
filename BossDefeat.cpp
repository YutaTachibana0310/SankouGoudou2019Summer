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
	entity->ChargeExplode(effect, core);
}

/**************************************
�O���[�o���ϐ�
***************************************/
int BossEnemyModel::BossDefeat::OnUpdate(BossEnemyModel* entity)
{
	const int AnimationChangeTiming = 10;
	const int FinishTiming = 240;

	cntFrame++;

	effect->pos = entity->actor->GetActorPosition();
	core->pos = entity->actor->GetActorPosition();

	if(cntFrame == AnimationChangeTiming)
		entity->actor->ChangeAnimation(BossEnemyActor::AnimID::Defeat);

	if (cntFrame == FinishTiming)
	{
		entity->isDestroyed = true;
		entity->Explode();
	}

	return BossEnemyModel::State::Defeat;
}
