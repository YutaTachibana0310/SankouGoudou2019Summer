//=====================================
//
//�g���C���R���C�_�[�w�b�_[TrailCollider.h]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _TRAILCOLLIDER_H_
#define _TRAILCOLLIDER_H_

#include "main.h"
#include "LineTrailModel.h"

/**************************************
�}�N����`
***************************************/

/**************************************
�n�_�E�I�_��`
***************************************/

/**************************************
�g���C���R���C�_�[�N���X
***************************************/
class TrailCollider
{
public:
	friend class TrailCollider;

	TrailCollider() {};
	~TrailCollider() {};

	bool CheckCollision(TrailCollider *other);
	void SetTrailIndex(LineTrailModel model);
	void SetAddressZ(float* adrPosZ);

private:
	LineTrailModel model;
	float *posZ;
};


#endif