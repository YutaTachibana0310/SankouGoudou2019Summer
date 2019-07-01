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

	if (entity->cntFrame < 60)
	{
		DebugLog("EnemyModel is stand by");
	}
	else if (entity->cntFrame < 120)
	{
		DebugLog("EnemyModel is Attack");
	}
	else
	{
		DebugLog("EnemyModel is Escape");
	}

	if (entity->cntFrame == 180)
		entity->cntFrame = 0;

	return StateContinuous;
}