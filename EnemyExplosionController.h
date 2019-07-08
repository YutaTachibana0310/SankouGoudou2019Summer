//=====================================
//
//エネミーエクスプロージョンコントローラヘッダ[EnemyExplosionController.h]
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _ENEMYEXPLOSIONCONTROLLER_H_
#define _ENEMYEXPLOSIONCONTROLLER_H_

#include "main.h"
#include "Framework\BaseParticleController.h"

/**************************************
マクロ定義
***************************************/

/**************************************
クラス定義
***************************************/
class EnemyExplosionController : public BaseParticleController
{
public:
	void Init();
	void Emit();
};

#endif