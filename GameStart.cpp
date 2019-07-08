//=====================================
//
//�Q�[���X�^�[�g����[GameStart.cpp]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "GameStart.h"

/**************************************
�}�N����`
***************************************/
#define GAMESTART_DURATION		(60)

/**************************************
���ꏈ��
***************************************/
void GameStart::OnStart(GameScene *entity)
{
	entity->cntFrame = 0;

	//TODO:�����ŃQ�[���X�^�[�g�̃e���b�v���Đ�����

}

/**************************************
�X�V����
***************************************/
int GameStart::OnUpdate(GameScene *entity)
{
	entity->cntFrame++;
	
	if (entity->cntFrame == GAMESTART_DURATION)
		return STATE_FINISHED;
	else
		return STATE_CONTINUOUS;
}