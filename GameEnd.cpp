//=====================================
//
//�Q�[���G���h����[GameEnd.cpp]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "GameEnd.h"
#include "masktex.h"

/**************************************
�}�N����`
***************************************/
#define GAMEEND_DURATION	(60)

/**************************************
���ꏈ��
***************************************/
void GameScene::GameEnd::OnStart(GameScene *entity)
{
	entity->cntFrame = 0;

	//TODO�F�����ŃQ�[���I���e���b�v���Đ�����
}

/**************************************
�X�V����
***************************************/
int GameScene::GameEnd::OnUpdate(GameScene *entity)
{
	entity->cntFrame++;

	entity->UpdateWhole();

	if (entity->cntFrame == 300)
	{
		SceneChangeFlag(true, Scene::SceneResult);
	}

	return GameScene::State::End;
}