//=====================================
//
//�Q�[���o�g������[GameBattle.cpp]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "GameBattle.h"
#include "TrailCollider.h"
#include "EnemyController.h"
#include "InputController.h"
#include "PlayerObserver.h"
#include "Framework\BoxCollider3D.h"
#include "sound.h"

/**************************************
�}�N����`
***************************************/
#define GAMEBATTLE_DURATION		(60*60)	//�Ƃ肠�����o�g����1���Ԃ����s���i���ŗp�j

/**************************************
���ꏈ��
***************************************/
void GameBattle::OnStart(GameScene *entity)
{
	entity->cntFrame = 0;
	Sound::GetInstance()->playsound = true;
}

/**************************************
�X�V����
***************************************/
int GameBattle::OnUpdate(GameScene *entity)
{
	int result = GameScene::State::Battle;

	entity->cntFrame++;

	//���͊m�F
	entity->playerObserver->CheckInput();

	//�G�l�~�[��������
	entity->enemyController->SetEnemy();

	//�Q�[���S�̂��X�V
	entity->UpdateWhole();

	//�{���o�[���˔���
	if (entity->ShouldFireBomber())
		result = GameScene::State::BombSequence;

	//�Փ˔���
	TrailCollider::UpdateCollision();
	BoxCollider3D::UpdateCollision();

	//�I������
	if (entity->cntFrame == GAMEBATTLE_DURATION)
		result = GameScene::State::End;

	return result;
	
}
