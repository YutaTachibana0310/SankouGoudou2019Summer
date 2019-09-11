//=====================================
//
//�Q�[���G���h����[GameEnd.cpp]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "GameEnd.h"
#include "masktex.h"
#include "GameSceneUIManager.h"
#include "Framework\PlayerPrefs.h"

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
}

/**************************************
�X�V����
***************************************/
int GameScene::GameEnd::OnUpdate(GameScene *entity)
{
	entity->cntFrame++;

	entity->UpdateWhole();

	const int TelopTiming = 360;
	const int Duration = 540;

	if (entity->cntFrame == TelopTiming)
	{
		entity->gameSceneUIManager->SetStageClearTelop();
	}

	if (entity->cntFrame == Duration)
	{
		PlayerPrefs::SaveBool("GameResult", true);
		SceneChangeFlag(true, Scene::SceneResult);
	}

	return GameScene::State::End;
}