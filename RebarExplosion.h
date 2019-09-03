//=====================================
//
//RebarExplosion.h
//機能:鉄骨の爆発エフェクト
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _REBAREXPLOSION_H_
#define _REBAREXPLOSION_H_

#include "main.h"
#include "Framework\AnimationParticle.h"
#include "Framework\BaseEmitter.h"
#include "Framework\BaseParticleController.h"

/**************************************
前方宣言
***************************************/

/**************************************
RebarExplosionクラス
***************************************/
class RebarExplosion : public AnimationParticle
{
public:
	RebarExplosion();

	void Init();
	void Update();
};

/**************************************
RebarExplosionEmitterクラス
***************************************/
class RebarExplosionEmitter : public BaseEmitter
{
	using BaseEmitter::BaseEmitter;
public:
	void Init();
	void Update();
};

/**************************************
RebarExplosionControllerクラス
***************************************/
class RebarExplosionController : public BaseParticleController
{
	void Init();
	void Emit();
};

#endif