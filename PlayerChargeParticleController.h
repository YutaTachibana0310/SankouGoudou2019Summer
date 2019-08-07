//=====================================
//
//プレイヤーチャージパーティクルコントローラヘッダ[PlayerChargeParticleController.h]
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _PLAYERCHARGEPARTICLECONTROLLER_H_
#define _PLAYERCHARGEPARTICLECONTROLLER_H_

#include "main.h"
#include "Framework\BaseParticleController.h"

/**************************************
マクロ定義
***************************************/

/**************************************
クラス定義
***************************************/
class PlayerChargeParticleController : public BaseParticleController
{
	void Init();
	void Emit();
};

#endif