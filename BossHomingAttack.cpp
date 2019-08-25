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

	int result = BossEnemyModel::State::HomingAttack;

	if (cntFrame == 120)
	{
		entity->FireBullet();
	}

	if (cntFrame == 300)
	{
		result = BossEnemyModel::State::Idle;
	}
	return result;
}
