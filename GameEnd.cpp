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
void GameEnd::OnStart(GameScene *entity)
{
	entity->cntFrame = 0;
	SceneChangeFlag(true, Scene::SceneResult);

	//TODO�F�����ŃQ�[���I���e���b�v���Đ�����
}

/**************************************
�X�V����
***************************************/
int GameEnd::OnUpdate(GameScene *entity)
{
	entity->cntFrame++;

	entity->UpdateWhole();

	return GameScene::State::End;
}