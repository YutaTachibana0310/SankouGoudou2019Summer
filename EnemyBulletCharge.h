//=====================================
//
//�G�l�~�[�o���b�g�`���[�W�w�b�_[EnemyBulletCharge.h]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _ENEMYBULLETCHARGE_H_
#define _ENEMYBULLETCHARGE_H_

#include "main.h"
#include "Framework\AnimationParticle.h"
#include "Framework\BaseEmitter.h"

/**************************************
�}�N����`
***************************************/

/**************************************
EnemyBulletCharge�N���X
***************************************/
class EnemyBulletCharge : public AnimationParticle
{
public:
	void Init();
	void Update();
};

/**************************************
EnemyBulletChargeEmitter�N���X
***************************************/
class EnemyBulletChargeEmitter : public BaseEmitter
{
public:
	void Init();
	void Update();
};

#endif