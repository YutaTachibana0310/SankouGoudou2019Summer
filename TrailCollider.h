//=====================================
//
//�g���C���R���C�_�[�w�b�_[TrailCollider.h]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _TRAILCOLLIDER_H_
#define _TRAILCOLLIDER_H_

#include "main.h"

/**************************************
�}�N����`
***************************************/

/**************************************
�n�_�E�I�_��`
***************************************/
enum class TrailIndex
{
	Top,
	MiddleLeft,
	LowerLeft,
	LowerRight,
	MiddleRight,
	Max
};

/**************************************
�g���C���R���C�_�[�N���X
***************************************/
class TrailCollider
{
public:
	TrailCollider() {};
	~TrailCollider() {};

	bool CheckCollision(TrailCollider *other);
	void SetTrailIndex(TrailIndex start, TrailIndex end);
	void SetAddressZ(float* adrPosZ);

private:
	TrailIndex start, end;
	float *posZ;
};


#endif