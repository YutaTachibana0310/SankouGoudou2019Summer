//=====================================
//
//�{�X�o�g���{���o�[�V�[�P���X����[GameBossBombSequence.cpp]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "GameBossBombSequence.h"
#include "PlayerObserver.h"
#include "GameParticleManager.h"
#include "BossController.h"

/**************************************
�O���[�o���ϐ�
***************************************/

/**************************************
���ꏈ��
***************************************/
void GameScene::GameBossBombSequence::OnStart(GameScene * entity)
{
	entity->playerObserver->OnStartBomberSequence();
	entity->useDarkMask = true;
	cntFrame = 0;
}

/**************************************
�X�V����
***************************************/
int GameScene::GameBossBombSequence::OnUpdate(GameScene * entity)
{
	const int BomberFireTiming = 80;
	const int StateDuration = 120;

	cntFrame++;

	int result = GameScene::State::BossBombSequence;

	//�v���C���[�̃A�j���[�V��������������
	entity->playerObserver->Update();
	
	//�{���o�[�̃G�t�F�N�g�����X�V����
	entity->particleManager->UpdateBombParticle();

	//���˃^�C�~���O�ł���Δ���
	if (cntFrame == BomberFireTiming)
	{
		std::shared_ptr<BossEnemyModel> target = entity->bossController->GetBoss();
		entity->playerObserver->FirePlayerBomber(target);
	}

	//�I������
	if (cntFrame == StateDuration)
	{
		entity->playerObserver->OnFinishBomberSequence();
		
		entity->useDarkMask = false;

		result = GameScene::State::BossBattle;
	}

	return result;
}
