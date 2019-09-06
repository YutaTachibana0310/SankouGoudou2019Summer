//=====================================
//
//�Q�[���{�X�o�g������[GameBossBattle.cpp]
//Author:GP12A332 21 ���ԗY��
//
//=====================================
#include "GameBossBattle.h"
#include "BossController.h"
#include "PlayerObserver.h"

/**************************************
�}�N����`
***************************************/

/**************************************
���ꏈ��
***************************************/
void GameScene::GameBossBattle::OnStart(GameScene* entity)
{
	entity->bossController->SetActive(true);
}

/**************************************
�X�V����
***************************************/
int GameScene::GameBossBattle::OnUpdate(GameScene* entity)
{
	int result = GameScene::State::BossBattle;

	entity->cntFrame++;

	//���͊m�F
	entity->playerObserver->CheckInput();

	//�Q�[���S�̂��X�V
	entity->UpdateWhole();

	//�{���o�[���˔���
	if (entity->ShouldFireBomberOnBossBattle())
		result = GameScene::State::BossBombSequence;

	//�Փ˔���
	TrailCollider::UpdateCollision();
	BoxCollider3D::UpdateCollision();

	//�{�X�̌��j����
	if (!entity->bossController->IsActive())
	{
		result = GameScene::State::End;
	}

	//�Q�[���I�[�o�[����
	if (!entity->playerObserver->IsAlive())
	{
		result = GameScene::State::Failed;
	}

	return result;
}
