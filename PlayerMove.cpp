//=====================================
//
//�v���C���[���[�u����[PlayerMove.cpp]
//Author:GP12B332 12 ����
//
//=====================================

#include "PlayerMove.h"
#include "Framework/Easing.h"
#include "PlayerController.h"
/**************************************
�}�N����`
***************************************/

/**************************************
�\���̒�`
***************************************/

/**************************************
�v���g�^�C�v�錾
***************************************/
void PlayerMove::OnUpdate(Player *entity)
{
	entity->cntFrame++;
	float t = (float)entity->cntFrame / PLAYER_MOVE_TIME;
	entity->pos = Easing<D3DXVECTOR3>::GetEasingValue(t, &entity->initpos, &entity->goalpos, EasingType::InCubic);

	if (entity->cntFrame == PLAYER_MOVE_TIME)
	{
		ChangeState(entity, PlayerState::Wait);
	}
}

void PlayerMove::OnStart(Player *entity)
{
	//������
	entity->cntFrame = 0;
	entity->initpos = entity->pos;
}

void PlayerMove::OnExit(Player * entity)
{
	//�ړ��I��	�o���b�g����
	entity->goalpos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);


}
