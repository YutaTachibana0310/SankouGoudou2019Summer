//=====================================
//
//エネミーバレットファイアコントローラヘッダ[EnemyBulletFireController.h]
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _ENEMYBULLETFIRECONTROLLER_H_
#define _ENEMYBULLETFIRECONTROLLER_H_

#include "main.h"
#include "Framework\BaseParticleController.h"

/**************************************
マクロ定義
***************************************/

/**************************************
クラス定義
***************************************/
class EnemyBulletFireController : public BaseParticleController
{
public:
	void Init();
	void Emit();
};

#endif