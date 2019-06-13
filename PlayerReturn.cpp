//=====================================
//
//�v���C���[���[�u����[PlayerMove.cpp]
//Author:GP12B332 12 ����
//
//=====================================

#include "PlayerReturn.h"
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


/*************************************
�X�V����
**************************************/
void PlayerReturn::OnUpdate(Player *entity)
{
	
	float t = (float)entity->cntFrame / 60;
	entity->cntFrame++;
	entity->pos = Easing<D3DXVECTOR3>::GetEasingValue(t, &entity->initpos, &PLAYER_CENTER, EasingType::OutExponential);
	
	if (entity->cntFrame == 60)
	{
		ChangeState(entity, PlayerState::Wait);
	}
};

/*************************************
������
**************************************/
void PlayerReturn::OnStart(Player * entity)
{
	entity->cntFrame = 0;
	entity->initpos = entity->pos;

};
/*************************************
�I������
**************************************/
void PlayerReturn::OnExit(Player *entity)
{

};
