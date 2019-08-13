//=====================================
//
//エネミーワープホールコントローラヘッダ[EnemyWarpHoleController.h]
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _ENEMYWARPHOLECONTROLLER_H_
#define _ENEMYWARPHOLECONTROLLER_H_

#include "main.h"
#include "Framework\BaseParticleController.h"

/**************************************
マクロ定義
***************************************/

/**************************************
クラス定義
***************************************/
class EnemyWarpHoleController : public BaseParticleController
{
public:
	void Init();
	void Emit();
};

#endif