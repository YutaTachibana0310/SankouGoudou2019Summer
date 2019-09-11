//=====================================
//
//TutorialScene::TutorialIdle.cpp
//�@�\:
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "TutorialIdle.h"
#include "TutorialScene.h"
#include "TutorialBG.h"
#include "GameSceneUIManager.h"
#include "PlayerObserver.h"
#include "PlayerController.h"
#include "InputController.h"
#include "GameParticleManager.h"
#include "TutorialController.h"
#include "TutorialEnemyController.h"
#include "ScoreManager.h"

/**************************************
�O���[�o���ϐ�
***************************************/

/**************************************
���ꏈ��
***************************************/
void TutorialScene::TutorialIdle::OnStart(TutorialScene * entity)
{
	//���ɂ�邱�ƂȂ�
}

/**************************************
�X�V����
***************************************/
int TutorialScene::TutorialIdle::OnUpdate(TutorialScene * entity)
{
	int result = TutorialScene::State::Idle;
	//���͊m�F
	entity->playerObserver->CheckInput();

	//�{���o�[���ˊm�F
	if (entity->ShouldFireBomber())
	{

		result = TutorialScene::State::Bomber;
	}

	//�e�I�u�W�F�N�g�X�V
	entity->bg->Update();
	entity->playerObserver->Update();
	entity->enemyController->Update();

	//�`���[�g���A���K�C�h�X�V
	entity->controller->Update();

	//�p�[�e�B�N���X�V
	GameParticleManager::Instance()->Update();

	//�Փ˔���
	TrailCollider::UpdateCollision();
	BoxCollider3D::UpdateCollision();

	return result;
}
