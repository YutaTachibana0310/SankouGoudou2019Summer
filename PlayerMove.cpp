//=====================================
//
//�v���C���[���[�u����[PlayerMove.cpp]
//Author:GP12B332 12 ����
//
//=====================================
#include "PlayerMove.h"
#include "Framework/Easing.h"

/**************************************
�}�N����`
***************************************/
#define PLAYER_MOVE_DURATION	(20)

/**************************************
�\���̒�`
***************************************/

/**************************************
�X�V����
***************************************/
int PlayerMove::OnUpdate(Player *entity)
{
	entity->cntFrame++;
	float t = (float)entity->cntFrame / PLAYER_MOVE_DURATION;
	entity->transform.pos = Easing::EaseValue(t, entity->initpos, entity->goalpos, EaseType::OutCubic);

	if (entity->cntFrame == PLAYER_MOVE_DURATION)
	{
		OnExit(entity);
		return STATE_FINISHED;
	}

	return STATE_CONTINUOUS;
}

/**************************************
���ꏈ��
***************************************/
void PlayerMove::OnStart(Player *entity)
{
	//������
	entity->cntFrame = 0;
	entity->initpos = entity->transform.pos;
}

/**************************************
�ޏꏈ��
***************************************/
void PlayerMove::OnExit(Player * entity)
{
}
