//=====================================
//
//�ҋ@����[PlayerWait.cpp]
//Author:GP12B332 12 ����
//
//=====================================
#include "PlayerWait.h"

/**************************************
�}�N����`
***************************************/
#define PLAYERWAIT_DURATION		(180)

/**************************************
�\���̒�`
***************************************/

/**************************************
�v���g�^�C�v�錾
***************************************/


/*************************************
�X�V����
**************************************/
int PlayerWait::OnUpdate(Player *entity)
{
	if (entity->inputInterval == PLAYERWAIT_DURATION)
		return STATE_FINISHED;
	else
		return STATE_CONTINUOUS;
}

/*************************************
���ꏈ��
**************************************/
void PlayerWait::OnStart(Player *entity)
{
	entity->cntFrame = 0;
	entity->inputInterval = 0;

	entity->animation->ChangeAnim(PlayerAnimID::Flying, 1.5f, true);
}

/*************************************
�ޏꏈ��
**************************************/
void PlayerWait::OnExit(Player *entity)
{

}
