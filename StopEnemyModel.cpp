//=====================================
//
//�X�g�b�v�G�l�~�[���f������[StopEnemyModel.cpp]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "StopEnemyModel.h"

/**************************************
�}�N����`
***************************************/
//����������Ă��瓖���蔻�肪�A�N�e�B�u�ɂȂ�^�C�~���O
#define STOPENEMY_TIME_COLLIDER_ACTIVATE	(60)

//�����蔻�肪�����ɂȂ�^�C�~���O
#define STOPENEMT_TIME_ESCAPE				(300 + STOPENEMY_TIME_COLLIDER_ACTIVATE)

//�I���^�C�~���O
#define STOPENEMY_TIME_UNINIT				(60 + STOPENEMT_TIME_ESCAPE)

/**************************************
�\���̒�`
***************************************/

/**************************************
�O���[�o���ϐ�
***************************************/

/**************************************
���ꏈ��
***************************************/
void StopEnemyModel::OnStart(EnemyModel *entity)
{
	entity->cntFrame = 0;

	//EnemyModel�ɑ�����Enemy�Ɉړ��w�����o��
}

/**************************************
�X�V����
***************************************/
int StopEnemyModel::OnUpdate(EnemyModel *entity)
{
	entity->cntFrame++;

	//60�t���[���ڂœ����蔻����A�N�e�B�u�ɂ���
	if (entity->cntFrame == STOPENEMY_TIME_COLLIDER_ACTIVATE)
		entity->collider->active = true;

	//�A�N�e�B�u�ɂȂ��Ă���300�t���[���ŗ��E����
	if (entity->cntFrame == STOPENEMT_TIME_ESCAPE)
		entity->collider->active = false;

	//���E�J�n���Ă���60�t���[���ŏI������
	if (entity->cntFrame == STOPENEMY_TIME_UNINIT)
		entity->Uninit();

	return StateContinuous;
}

/**************************************
�ޏꏈ��
***************************************/
void StopEnemyModel::OnExit(EnemyModel *entity)
{

}