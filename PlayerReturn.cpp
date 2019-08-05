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
int PlayerReturn::OnUpdate(Player *entity)
{
	float t = (float)entity->cntFrame / PLAYER_RETURN_DURATION;
	entity->cntFrame++;
	entity->transform.pos = Easing::EaseValue(t, entity->initpos, entity->goalpos, EaseType::OutCubic);
	
	if (entity->cntFrame == PLAYER_RETURN_DURATION)
	{
		OnExit(entity);
		return STATE_FINISHED;
	}

	return STATE_CONTINUOUS;
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

};
