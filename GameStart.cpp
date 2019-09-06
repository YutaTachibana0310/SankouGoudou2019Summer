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
void GameScene::GameStart::OnStart(GameScene *entity)
{
	entity->cntFrame = 0;

	//TODO:�����ŃQ�[���X�^�[�g�̃e���b�v���Đ�����

}

/**************************************
�X�V����
***************************************/
int GameScene::GameStart::OnUpdate(GameScene *entity)
{
	entity->cntFrame++;

	entity->UpdateWhole();
	
	if (entity->cntFrame == GAMESTART_DURATION)
		return GameScene::State::Battle;
	else
		return GameScene::State::Failed;
}