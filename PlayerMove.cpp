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

/**************************************
�\���̒�`
***************************************/

/**************************************
�v���g�^�C�v�錾
***************************************/
void PlayerMove::OnUpdate(Player *entity)
{
	float t = (float)entity->cntFrame / 120;
	entity->pos = Easing<D3DXVECTOR3>::GetEasingValue(t, &entity->initpos, &entity->goalpos, EasingType::InCubic);
	
}

void PlayerMove::OnStart(Player *entity)
{
	//������
	entity->cntFrame = 0;
	entity->goalpos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	
}

void PlayerMove::OnExit(Player * entity)
{
	//�ړ��I��	�o���b�g����


}
