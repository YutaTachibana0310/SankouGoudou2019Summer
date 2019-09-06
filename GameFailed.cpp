//=====================================
//
//GameFailed.cpp
//�@�\:�Q�[���I�[�o�[�X�e�[�g
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "GameFailed.h"
#include "PostEffect\MonotoneFilter.h"
#include "PostEffectManager.h"
#include "GameOver.h"
#include "masktex.h"

/**************************************
�O���[�o���ϐ�
***************************************/

/**************************************
���ꏈ��
***************************************/
void GameScene::GameFailed::OnStart(GameScene * entity)
{
	cntFrame = 0;
}

/**************************************
�X�V����
***************************************/
int GameScene::GameFailed::OnUpdate(GameScene * entity)
{
	cntFrame++;

	float t = 1.0f * cntFrame / MonotoneDuration;
	MonotoneFilter::Instance()->SetPower(t);

	entity->UpdateWhole();
	entity->gameover->Update();

	if (cntFrame == TransitionDuration)
	{
		SceneChangeFlag(true, Scene::SceneResult);
	}

	return GameScene::State::Failed;
}
