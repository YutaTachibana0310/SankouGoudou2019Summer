//=====================================
//
//�G�l�~�[�o���b�g�G�t�F�N�g�w�b�_[EnemyBulletEffect.h]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _ENEMYBULLETEFFECT_H_
#define _ENEMYBULLETEFFECT_H_

#include "main.h"
#include "Framework\AnimationParticle.h"
#include "Framework\BaseEmitter.h"

/**************************************
�}�N����`
***************************************/

/**************************************
EnemyBulletEffect�N���X
***************************************/
class EnemyBulletEffect : public AnimationParticle
{
public:
	void Init();
	void Update();
};

/**************************************
EnemyBulletEffectEmitter�N���X
***************************************/
class EnemyBulletEffectEmitter : public BaseEmitter
{
public:
	void Init();
	void Update();
	
	D3DXVECTOR3 edgeR, edgeL;
};

#endif