//=====================================
//
//�G�l�~�[�G�N�X�v���[�W�����w�b�_[EnemyExplosionParticle.h]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _ENEMYEXPLOSIONPARTICLE_H_
#define _ENEMYEXPLOSIONPARTICLE_H_

#include "main.h"
#include "Framework\AnimationParticle.h"
#include "Framework\BaseEmitter.h"

/**************************************
�}�N����`
***************************************/

/**************************************
EnemyExplosionParticle�N���X
***************************************/
class EnemyExplosionParticle : public AnimationParticle
{
public:
	void Init();
	void Uninit();
	void Update();
};

/**************************************
EnemyExplosionEmitter�N���X
***************************************/
class EnemyExplosionEmitter : public BaseEmitter
{
public:
	void Init();
	void Uninit();
	void Update();

};
#endif