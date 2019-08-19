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
void GameBossBattle::OnStart(GameScene* entity)
{
	entity->bossController->SetActive(true);
}

/**************************************
�X�V����
***************************************/
int GameBossBattle::OnUpdate(GameScene* entity)
{
	int result = GameScene::State::Battle;

	entity->cntFrame++;

	//���͊m�F
	entity->playerObserver->CheckInput();

	//�Q�[���S�̂��X�V
	entity->UpdateWhole();

	//�{���o�[���˔���
	if (entity->ShouldFireBomber())
		result = GameScene::State::BombSequence;

	//�Փ˔���
	TrailCollider::UpdateCollision();
	BoxCollider3D::UpdateCollision();

	//�{�X�̌��j����

	return result;
}
