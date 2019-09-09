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
#include "PlayerObserver.h"

/**************************************
�O���[�o���ϐ�
***************************************/

/**************************************
���ꏈ��
***************************************/
void GameScene::GameFailed::OnStart(GameScene * entity)
{
	cntFrame = 0;
	entity->playerObserver->OnGameOver();
}

/**************************************
�X�V����
***************************************/
int GameScene::GameFailed::OnUpdate(GameScene * entity)
{
	cntFrame++;

	//���m�g�[���t�B���^�̋������v�Z
	float t = 1.0f * cntFrame / MonotoneDuration;
	MonotoneFilter::Instance()->SetPower(t);

	//�Q�[���S�̂�GAMEOVER�\�����X�V
	entity->UpdateWhole();
	entity->gameover->Update();

	//�w�莞�Ԍo�߂��Ă�����V�[���J��
	if (cntFrame == TransitionDuration)
	{
		SceneChangeFlag(true, Scene::SceneResult);
	}

	return GameScene::State::Failed;
}
