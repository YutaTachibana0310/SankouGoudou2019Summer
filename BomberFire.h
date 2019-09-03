//=====================================
//
//�{���o�[�t�@�C�A�w�b�_[BomberFire.h]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _BOBMERFIRE_H_
#define _BOBMERFIRE_H_

#include "main.h"
#include "Framework\AnimationParticle.h"
#include "Framework\BaseEmitter.h"

/**************************************
�}�N����`
***************************************/

/**************************************
BomberFire�N���X
***************************************/
class BomberFire : public AnimationParticle
{
public:
	BomberFire();

	void Init();
	void Update();

private:
	D3DXVECTOR3 moveDir;
	float speed;
};

/**************************************
BomberFireEmitter�N���X
***************************************/
class BomberFireEmitter : public BaseEmitter
{
public:
	void Init();
	void Update();
};

#endif