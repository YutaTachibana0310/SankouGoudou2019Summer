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
void PlayerMove::OnUpdate(Player *entity)
{
	entity->cntFrame++;
	float t = (float)entity->cntFrame / PLAYER_MOVE_DURATION;
	entity->transform.pos = Easing<D3DXVECTOR3>::GetEasingValue(t, &entity->initpos, &entity->goalpos, EasingType::OutCubic);

	if (entity->cntFrame == PLAYER_MOVE_DURATION)
	{
		OnExit(entity);
	}
}

/**************************************
���ꏈ��
***************************************/
void PlayerMove::OnStart(Player *entity)
{
	//������
	entity->cntFrame = 0;
	entity->initpos = entity->transform.pos;
	entity->trail->Init(&entity->transform.pos);
}

/**************************************
�ޏꏈ��
***************************************/
void PlayerMove::OnExit(Player * entity)
{
	entity->trail->Uninit();

	if (callback != NULL)
		callback();
}
