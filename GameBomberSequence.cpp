//=====================================
//
//�Q�[���{���o�[�V�[�P���X����[GameBomberSequence.cpp]
//Author:GP12A332 21 ���ԗY��
//
//=====================================
#include "GameBomberSequence.h"
#include "PlayerObserver.h"
#include "GameParticleManager.h"
#include "EnemyController.h"

#include <vector>

using namespace std;
/**************************************
�}�N����`
***************************************/
#define GAMEBOMBERSEQUENCE_DURATION		(120)
#define GAMEBOMBERSEQUENCE_LAUNCH_TIME	(80)

/**************************************
���ꏈ��
***************************************/
void GameScene::GameBomberSequence::OnStart(GameScene* entity)
{
	entity->playerObserver->OnStartBomberSequence();
	entity->useDarkMask = true;
	cntFrame = 0;
}

/**************************************
�X�V����
***************************************/
int GameScene::GameBomberSequence::OnUpdate(GameScene* entity)
{
	cntFrame++;

	int result = GameScene::State::BombSequence;

	//�v���C���[�̃A�j���[�V��������������
	entity->playerObserver->Update();

	//�{���o�[�̃G�t�F�N�g�����X�V����
	entity->particleManager->UpdateBombParticle();

	//���˃^�C�~���O�ł���΃{���o�[����
	if (cntFrame == GAMEBOMBERSEQUENCE_LAUNCH_TIME)
	{
		list<Enemy*> targetList;
		entity->enemyController->GetEnemyList(targetList);
		entity->playerObserver->FirePlayerBomber(targetList);
	}

	//�I������
	if (cntFrame == GAMEBOMBERSEQUENCE_DURATION)
	{
		entity->playerObserver->OnFinishBomberSequence();
		entity->enemyController->OnFinishBombSequence();
		entity->useDarkMask = false;

		result = entity->prevState;
	}

	return result;	
}