//=====================================
//
//�Q�[���o�g������[GameBattle.cpp]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "GameBattle.h"
#include "TrailCollider.h"
#include "EnemyController.h"

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
}

/**************************************
�X�V����
***************************************/
int GameBattle::OnUpdate(GameScene *entity)
{
	entity->cntFrame++;

	//�G�l�~�[��������
	entity->enemyController->SetEnemy();

	//�Փ˔���
	TrailCollider::UpdateCollision();

	if (entity->cntFrame == GAMEBATTLE_DURATION)
		return STATE_FINISHED;
	else
		return STATE_CONTINUOUS;
}