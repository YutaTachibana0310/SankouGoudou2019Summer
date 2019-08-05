//=====================================
//
//�Q�[���{���o�[�V�[�P���X����[GameBomberSequence.cpp]
//Author:GP12A332 21 ���ԗY��
//
//=====================================
#include "GameBomberSequence.h"
#include "PlayerObserver.h"
#include "GameParticleManager.h"

/**************************************
�}�N����`
***************************************/
#define GAMEBOMBERSEQUENCE_DURATION		(120)

/**************************************
���ꏈ��
***************************************/
void GameBomberSequence::OnStart(GameScene* entity)
{
	entity->playerObserver->OnStartBomberSequence();
	cntFrame = 0;
}

/**************************************
�X�V����
***************************************/
int GameBomberSequence::OnUpdate(GameScene* entity)
{
	cntFrame++;

	int result = GameScene::State::BombSequence;

	//�v���C���[�̃A�j���[�V��������������
	entity->playerObserver->Update();

	//�p�[�e�B�N���̍X�V
	entity->particleManager->Update();

	if (cntFrame == GAMEBOMBERSEQUENCE_DURATION)
	{
		entity->playerObserver->OnFinishBomberSequence();
		result = GameScene::State::Battle;
	}

	return result;
}