//=====================================
//
//�Q�[���G���h����[GameEnd.cpp]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "GameEnd.h"

/**************************************
�}�N����`
***************************************/
#define GAMEEND_DURATION	(60)

/**************************************
���ꏈ��
***************************************/
void GameEnd::OnStart(GameScene *entity)
{
	entity->cntFrame = 0;

	//TODO�F�����ŃQ�[���I���e���b�v���Đ�����
}

/**************************************
�X�V����
***************************************/
int GameEnd::OnUpdate(GameScene *entity)
{
	entity->cntFrame++;

	if (entity->cntFrame == GAMEEND_DURATION)
		return STATE_FINISHED;
	else
		return STATE_CONTINUOUS;
}