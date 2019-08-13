//=====================================
//
//�G�l�~�[�o���b�g�g���C���w�b�_[EnemyBulletTrail.h]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _ENEMYBULLETTRAIL_H_
#define _ENEMYBULLETTRAIL_H_

#include "main.h"
#include "Framework\AnimationParticle.h"
#include "Framework\BaseEmitter.h"

/**************************************
EnemyBulletTrail�N���X
***************************************/
class EnemyBulletTrail : public AnimationParticle
{
public:
	void Init();
	void Update();

	D3DXVECTOR3 moveDir;
	float speed;
};

/**************************************
EnemyBulletTrailEmitter�N���X
***************************************/
class EnemyBulletTrailEmitter : public BaseEmitter
{
public:
	void Init();
	void Update();

	D3DXVECTOR3 prevPos;
};

#endif