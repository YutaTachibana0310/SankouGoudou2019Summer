//=====================================
//
//プレイヤーチャージエフェクトコントローラヘッダ[PlayerChargeEffectController.h]
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _PLAYERCHARGEEFFECTCONTROLLER_H_
#define _PLAYERCHARGEEFFECTCONTROLLER_H_

#include "main.h"
#include "Framework\BaseParticleController.h"

/**************************************
マクロ定義
***************************************/

/**************************************
クラス定義
***************************************/
class PlayerChargeEffectController : public BaseParticleController
{
	void Init();
	void Emit();
};

#endif