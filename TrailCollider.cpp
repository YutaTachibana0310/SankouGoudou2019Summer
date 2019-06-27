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

	if(this->model != other->model)
		return false;

	//Z��������
	float dist = fabsf(*posZ - *(other->posZ));

	return dist < TRAILCOLLIDER_HIT_LENGTH;
	
}

/**************************************
�g���C���C���f�b�N�X�Z�b�g����
***************************************/
void TrailCollider::SetTrailIndex(LineTrailModel model)
{
	this->model = model;
}

/**************************************
Z���W�|�C���^�Z�b�g����
***************************************/
void TrailCollider::SetAddressZ(float* adrPosZ)
{
	this->posZ = adrPosZ;
}