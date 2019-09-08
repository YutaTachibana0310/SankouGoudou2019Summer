//=====================================
//
//�Q�[���G���h����[GameEnd.cpp]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "GameEnd.h"
#include "masktex.h"
#include "GameSceneUIManager.h"

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
	entity->gameSceneUIManager->SetStageClearTelop();
}

/**************************************
�X�V����
***************************************/
int GameScene::GameEnd::OnUpdate(GameScene *entity)
{
	entity->cntFrame++;

	entity->UpdateWhole();

	const int Duration = 420;
	if (entity->cntFrame == Duration)
	{
		SceneChangeFlag(true, Scene::SceneResult);
	}

	return GameScene::State::End;
}