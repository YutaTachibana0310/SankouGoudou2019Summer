//=====================================
//
//エネミーバレットチャージコントローラヘッダ[EnemyBulletChargeController.h]
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _ENEMYBULLETCHARGECONTROLLER_H_
#define _ENEMYBULLETCHARGECONTROLLER_H_

#include "main.h"
#include "Framework\BaseParticleController.h"

/**************************************
マクロ定義
***************************************/

/**************************************
クラス定義
***************************************/
class EnemyBulletChargeController : public BaseParticleController
{
public:
	void Init();
	void Emit();
};

#endif