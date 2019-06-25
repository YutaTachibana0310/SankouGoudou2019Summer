//=====================================
//
//�v���C���[���[�u����[PlayerMove.cpp]
//Author:GP12B332 12 ����
//
//=====================================
#include "PlayerReturn.h"
#include "Framework/Easing.h"

/**************************************
�}�N����`
***************************************/
#define PLAYER_RETURN_DURATION		(20)

/**************************************
�\���̒�`
***************************************/

/**************************************
�v���g�^�C�v�錾
***************************************/


/*************************************
�X�V����
**************************************/
void PlayerReturn::OnUpdate(Player *entity)
{
	float t = (float)entity->cntFrame / PLAYER_RETURN_DURATION;
	entity->cntFrame++;
	entity->transform.pos = Easing<D3DXVECTOR3>::GetEasingValue(t, &entity->initpos, &entity->goalpos, EasingType::OutCubic);
	
	if (entity->cntFrame == PLAYER_RETURN_DURATION)
	{
		OnExit(entity);
	}
};

/*************************************
���ꏈ��
**************************************/
void PlayerReturn::OnStart(Player * entity)
{
	entity->cntFrame = 0;
	entity->initpos = entity->transform.pos;
	entity->goalpos = D3DXVECTOR3(0.0f, -20.0f, 0.0f);
};

/*************************************
�ޏꏈ��
**************************************/
void PlayerReturn::OnExit(Player *entity)
{
	if (callback != NULL)
		callback();
};
