//=====================================
//
//�e�X�g�G�l�~�[���f������[TestEnemyModel.cpp]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "TestEnemyModel.h"
#include "debugWindow.h"

/**************************************
�}�N����`
***************************************/

/**************************************
�\���̒�`
***************************************/

/**************************************
�O���[�o���ϐ�
***************************************/

/**************************************
���ꏈ��
***************************************/
void TestEnemyModel::OnStart(EnemyModel *entity)
{
	entity->cntFrame = 0;
	entity->collider->active = false;
}

/**************************************
�ޏꏈ��
***************************************/
void TestEnemyModel::OnExit(EnemyModel *entity)
{

}

/**************************************
�X�V����
***************************************/
int TestEnemyModel::OnUpdate(EnemyModel *entity)
{
	entity->cntFrame++;

	//�Փ˔��胊�X�g�ɓo�^
	if(entity->cntFrame == 60)
	{
		entity->collider->active = true;
		return StateContinuous;
	}

	//�U��
	if (entity->cntFrame == 120)
	{

		return AttackTiming;
	}

	//�Փ˔��胊�X�g���痣�E
	if (entity->cntFrame == 180)
	{
		entity->collider->active = false;
		entity->cntFrame = 0;
		return StateContinuous;
	}

	DebugLog("cnt:%d", entity->cntFrame);

	return StateContinuous;
}