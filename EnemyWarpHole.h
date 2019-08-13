//=====================================
//
//�G�l�~�[���[�v�z�[���w�b�_[EnemyWarpHole.h]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _ENEMYWARPHOLE_H_
#define _ENEMYWARPHOLE_H_

#include "main.h"
#include "Framework\AnimationParticle.h"
#include "Framework\BaseEmitter.h"

/**************************************
�}�N����`
***************************************/

/**************************************
EnemyWarpHole�N���X
***************************************/
class EnemyWarpHole : public AnimationParticle
{
public:
	EnemyWarpHole();
	~EnemyWarpHole();

	void Init();
	void Update();
};

/**************************************
EnemyWarpHoleEmitter�N���X
***************************************/
class EnemyWarpHoleEmitter : public BaseEmitter
{
public:
	EnemyWarpHoleEmitter();
	~EnemyWarpHoleEmitter();

	void Init();
	void Update();
};

#endif