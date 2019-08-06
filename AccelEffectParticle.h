//=====================================
//
//アクセルエフェクトパーティクルヘッダ[AccelEffectParticle.h]
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _ACCELEFFECTPARTICLE_H_
#define _ACCELEFFECTPARTICLE_H_

#include "main.h"
#include "Framework\BaseParticle.h"
#include "Framework\BaseEmitter.h"

/**************************************
マクロ定義
***************************************/

/**************************************
AccelEffectParticleクラス
***************************************/
class AccelEffectParticle : public BaseParticle
{
public:
	void Init();
	void Update();

private:
	D3DXVECTOR3 moveDir;
	D3DXVECTOR3 baseScale;
};

/**************************************
AccelEffectParticleEmitterクラス
***************************************/
class AccelEffectParticleEmitter : public BaseEmitter
{
	void Init();
	void Update();
};

#endif