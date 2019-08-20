//=====================================
//
//�{�X������ԏ���[BossInit.cpp]
//Author:GP12A332 21 ���ԗY��
//
//=====================================
#include "BossInit.h"
#include "BossEnemyActor.h"
#include "Framework\Vector3.h"

/**************************************
�}�N����`
***************************************/
#define BOSSINIT_MOVE_DURATION		(180)
#define BOSSINIT_INITPOSITION		(D3DXVECTOR3(0.0f, 2000.0f, 1500.0f))
#define BOSSINIT_MOVE_POSITION		(D3DXVECTOR3(0.0f, -200.0f, 1500.0f))

/**************************************
���ꏈ��
***************************************/
void BossEnemyModel::BossInit::OnStart(BossEnemyModel *entity)
{
	entity->actor->transform.pos = BOSSINIT_INITPOSITION;
	entity->actor->Move(BOSSINIT_MOVE_POSITION, BOSSINIT_MOVE_DURATION);

	entity->actor->ChangeAnimation(BossEnemyActor::AnimID::Flying);

	cntFrame = 0;
}

/**************************************
�X�V����
***************************************/
int BossEnemyModel::BossInit::OnUpdate(BossEnemyModel *entity)
{
	cntFrame++;

	int result = BossEnemyModel::Init;
	if (cntFrame == BOSSINIT_MOVE_DURATION)
	{
		entity->actor->ChangeAnimation(BossEnemyActor::AnimID::Idle);
		result = BossEnemyModel::State::Damageable;
	}

	return result;
}
