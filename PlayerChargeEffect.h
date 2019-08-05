//=====================================
//
//プレイヤーチャージエフェクトヘッダ[PlayerChargeEffect.h]
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _PLAYERCHARGEEFFECT_H_
#define _PLAYERCHARGEEFFECT_H_

#include "main.h"
#include "Framework\AnimationParticle.h"
#include "Framework\BaseEmitter.h"

/**************************************
マクロ定義
***************************************/

/**************************************
PlayerChargeEffectクラス
***************************************/
class PlayerChargeEffect : public AnimationParticle
{
public:
	void Init();
	void Update();
};

/**************************************
PlayerChargeEffectEmitterクラス
***************************************/
class PlayerChargeEffectEmitter : public BaseEmitter
{
public:
	void Init();
	void Update();
};

#endif