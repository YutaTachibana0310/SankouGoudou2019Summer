//=====================================
//
//�{�X�z�[�~���O�A�^�b�N����[BossHomingAttack.cpp]
//Author:GP12A332 21 ���ԗY��
//
//=====================================
#include "BossHomingAttack.h"
#include "BossEnemyActor.h"

/**************************************
�}�N����`
***************************************/

/**************************************
���ꏈ��
***************************************/
void BossEnemyModel::BossHomingAttack::OnStart(BossEnemyModel *entity)
{
	cntFrame = 0;

	//�A�j���[�V�����J��
	entity->actor->ChangeAnimation(BossEnemyActor::AnimID::Attack01);

	//�o���b�g�`���[�W�J�n
	entity->StartBulletCharge();
}

/**************************************
�X�V����
***************************************/
int BossEnemyModel::BossHomingAttack::OnUpdate(BossEnemyModel* entity)
{
	cntFrame++;
	const int LoopMax[BossEnemyModel::Const::LevelMax] = { 2, 3, 3, 4 };

	int result = BossEnemyModel::State::HomingAttack;

	if (cntFrame == 90)
	{
		entity->NotifyBullet();
	}

	if (cntFrame == 120)
	{
		entity->FireBullet();
	}

	if (cntFrame == 150 && entity->cntLoop < LoopMax[entity->level])
	{
		entity->cntLoop++;
		OnStart(entity);
	}

	if (cntFrame == 300)
	{
		result = BossEnemyModel::State::Idle;
	}
	return result;
}
