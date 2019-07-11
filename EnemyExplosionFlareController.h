//=====================================
//
//エネミーエクスプロージョンフレアコントローラヘッダ[EnemyExplosionFlareController.h]
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _ENEMYEXPLOSIONFLARECONTROLLER_H_
#define _ENEMYEXPLOSIONFLARECONTROLLER_H_

#include "main.h"
#include "Framework\BaseParticleController.h"

/**************************************
マクロ定義
***************************************/

/**************************************
クラス定義
***************************************/
class EnemyExplosionFlareController : public BaseParticleController
{
public:
	void Init();
	void Emit();
};

#endif