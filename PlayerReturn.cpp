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
	float t = entity->cntFrame / 120;
	entity->pos = Easing<D3DXVECTOR3>::GetEasingValue(t, &entity->initpos, &PLAYER_INIT_POS, EasingType::OutExponential);

};

/*************************************
������
**************************************/
void PlayerReturn::OnStart(Player * entity)
{
	entity->cntFrame = 0;
};
/*************************************
�I������
**************************************/
void PlayerReturn::OnExit(Player *entity)
{

};
