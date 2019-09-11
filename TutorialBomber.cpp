//=====================================
//
//TutorialBomber.cpp
//�@�\:
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "TutorialBomber.h"
#include "TutorialEnemyController.h"
#include "PlayerObserver.h"
#include "GameParticleManager.h"

/**************************************
�O���[�o���ϐ�
***************************************/
#define TUTORIALBOMBERSEQUENCE_DURATION		(120)
#define TUTORIALBOMBERSEQUENCE_LAUNCH_TIME	(80)

/**************************************
���ꏈ��
***************************************/
void TutorialScene::TutorialBomber::OnStart(TutorialScene * entity)
{
	entity->playerObserver->OnStartBomberSequence();
	entity->useDarkMask = true;
	cntFrame = 0;
}


/**************************************
�X�V����
***************************************/
int TutorialScene::TutorialBomber::OnUpdate(TutorialScene * entity)
{
	int result = TutorialScene::State::Bomber;

	cntFrame++;

	//�v���C���[�̃A�j���[�V��������������
	entity->playerObserver->Update();

	//�{���o�[�̃G�t�F�N�g�����X�V����
	GameParticleManager::Instance()->UpdateBombParticle();

	//���˃^�C�~���O�ł���΃{���o�[����
	if (cntFrame == TUTORIALBOMBERSEQUENCE_LAUNCH_TIME)
	{
		list<shared_ptr<Enemy>> targetList;
		entity->enemyController->GetEnemyList(targetList);
		entity->playerObserver->FirePlayerBomber(targetList);
	}

	////�I������
	if (cntFrame == TUTORIALBOMBERSEQUENCE_DURATION)
	{
		entity->playerObserver->OnFinishBomberSequence();
		entity->useDarkMask = false;

		result = State::Idle;
	}

	return result;
}
