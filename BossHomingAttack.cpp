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
	const int LoopMax[BossEnemyModel::Const::LevelMax] = { 2, 3, 4 };
	const int NotifyTiming = 90;
	const int FireTiming = 120;
	const int LoopTiming = 150;
	const int FinishTiming = 300;

	int result = BossEnemyModel::State::HomingAttack;

	if (cntFrame == NotifyTiming)
	{
		entity->NotifyBullet();
	}

	if (cntFrame == FireTiming)
	{
		entity->FireBullet();
	}

	if (cntFrame == LoopTiming && entity->cntAttack < LoopMax[entity->level])
	{
		entity->cntAttack++;
		OnStart(entity);
	}

	if (cntFrame == FinishTiming)
	{
		entity->cntLoop++;
		result = BossEnemyModel::State::Idle;
	}
	return result;
}
