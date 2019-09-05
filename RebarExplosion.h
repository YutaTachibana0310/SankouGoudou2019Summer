//=====================================
//
//RebarExplosion.h
//�@�\:�S���̔����G�t�F�N�g
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _REBAREXPLOSION_H_
#define _REBAREXPLOSION_H_

#include "main.h"
#include "Framework\AnimationParticle.h"
#include "Framework\BaseEmitter.h"
#include "Framework\BaseParticleController.h"

/**************************************
�O���錾
***************************************/

/**************************************
RebarExplosion�N���X
***************************************/
class RebarExplosion : public AnimationParticle
{
public:
	RebarExplosion();

	void Init();
	void Update();
};

/**************************************
RebarExplosionEmitter�N���X
***************************************/
class RebarExplosionEmitter : public BaseEmitter
{
	using BaseEmitter::BaseEmitter;
public:
	void Init();
	void Update();
};

/**************************************
RebarExplosionController�N���X
***************************************/
class RebarExplosionController : public BaseParticleController
{
	void Init();
	void Emit();
};

#endif