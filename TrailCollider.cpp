//=====================================
//
//�g���C���R���C�_�[����[TrailCollider.cpp]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "TrailCollider.h"

/**************************************
�}�N����`
***************************************/
#define TRAILCOLLIDER_HIT_LENGTH		(20.0f)

/**************************************
�\���̒�`
***************************************/

/**************************************
�O���[�o���ϐ�
***************************************/

/**************************************
�Փ˔���
***************************************/
bool TrailCollider::CheckCollision(TrailCollider *other)
{
	bool isHit;

	//�n�_�ƏI�_�̈�v����
	isHit = (start == other->start && end == other->end) || (start == other->end && end == other->start);

	if (!isHit)
		return false;

	//Z��������
	float dist = fabsf(*posZ - *(other->posZ));

	return dist < TRAILCOLLIDER_HIT_LENGTH;
	
}

/**************************************
�p�����[�^�Z�b�g����
***************************************/
void TrailCollider::SetParam(TrailIndex start, TrailIndex end, float *adrPosZ)
{
	this->start = start;
	this->end = end;
	this->posZ = adrPosZ;
}
