//=====================================
//
//�x�[�X�p�[�e�B�N������[BaseParticle.cpp]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "BaseParticle.h"

/**************************************
�}�N����`
***************************************/

/**************************************
�\���̒�`
***************************************/

/**************************************
�O���[�o���ϐ�
***************************************/

/**************************************
�Z�b�g����
***************************************/
void BaseParticle::Set(D3DXVECTOR3 *setPos, int lifeFrame)
{
	pos = *setPos;
	cntFrame = 0;
	active = true;
	this->lifeFrame = lifeFrame;
}

/**************************************
�ړ��p�����[�^�Z�b�g����
***************************************/
void BaseParticle::SetMoveParameter(D3DXVECTOR3 *moveDir, float speed, EasingType easeType)
{
	D3DXVec3Normalize(&this->moveDir, moveDir);
	this->speed = speed;
	this->easeType = easeType;
}

/**************************************
�ړ�����
***************************************/
void BaseParticle::Update()
{
	if (!active)
		return;

	//�ړ�����
	float t = (float)cntFrame / (float)lifeFrame;
	float curSpeed = Easing<float>::GetEasingValue(t, &speed, &EndSpeed, easeType);
	pos += moveDir * curSpeed;

	//��������
	cntFrame++;
	if (cntFrame > lifeFrame)
		active = false;
}

/**************************************
�A�N�e�B�u����
***************************************/
bool BaseParticle::IsActive()
{
	return active;
}
