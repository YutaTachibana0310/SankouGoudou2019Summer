//=====================================
//
//ボスチャージエフェクト　ヘッダ[BossChargeEffect.h]
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _BOSSCHARGEFFECT_H_
#define _BOSSCHARGEFFECT_H_

#include "main.h"
#include "Framework\AnimationParticle.h"
#include "Framework\BaseEmitter.h"
#include "Framework\BaseParticleController.h"

/**************************************
前方宣言
***************************************/

/**************************************
マクロ・列挙子定義
***************************************/

/**************************************
BossChargeParticleクラス
***************************************/
class BossChargeParticle : public AnimationParticle
{
public:
	BossChargeParticle();

	void Init();
	void Update();
};

/**************************************
BossChargeEmitterクラス
***************************************/
class BossChargeEmitter : public BaseEmitter
{
public:
	void Init();
	void Update();
};

/**************************************
BossChargeParticleControllerクラス
***************************************/
class BossChargeParticleController : public BaseParticleController
{
public:
	void Init();
	void Emit();
};

#endif