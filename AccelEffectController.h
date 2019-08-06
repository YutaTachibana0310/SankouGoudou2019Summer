//=====================================
//
//アクセルエフェクトコントローラヘッダ[AccelEffectController.h]
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _ACCELEFFECTCONTROLLER_H_
#define _ACCELEFFECTCONTROLLER_H_

#include "main.h"
#include "Framework\BaseParticleController.h"

/**************************************
マクロ定義
***************************************/

/**************************************
クラス定義
***************************************/
class AccelEffectController : public BaseParticleController
{
public:
	void Init();
	void Emit();
};

#endif