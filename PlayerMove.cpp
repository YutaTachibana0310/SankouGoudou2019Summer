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
	entity->transform.pos = Easing<D3DXVECTOR3>::GetEasingValue(t, &entity->initpos, &entity->goalpos, EasingType::OutCubic);

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

	entity->animation->ChangeAnim(PlayerAnimID::Attack, 5.5f, true);
}

/**************************************
�ޏꏈ��
***************************************/
void PlayerMove::OnExit(Player * entity)
{
}
