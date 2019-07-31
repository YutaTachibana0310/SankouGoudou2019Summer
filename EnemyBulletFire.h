//=====================================
//
//�G�l�~�[�o���b�g�t�@�C�A�w�b�_[EnemyBulletFire.h]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _ENEMYBULLETFIRE_H_
#define _ENEMYBULLETFIRE_H_

#include "main.h"
#include "Framework\BaseParticle.h"
#include "Framework\BaseEmitter.h"

/**************************************
�}�N����`
***************************************/

/**************************************
EnemyBulletFire�N���X
***************************************/
class EnemyBulletFire : public BaseParticle
{
public:
	void Init();
	void Update();

private:
	D3DXVECTOR3 moveDir;
	float speed;
};

/**************************************
EnemyBullet�G�~�b�^�N���X
***************************************/
class EnemyBulletFireEmitter : public BaseEmitter
{
public:
	void Init();
	void Update();
};

#endif