//=====================================
//
//エネミーバレットトレイルコントローラヘッダ[EnemyBulletTrailController.h]
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _ENEMYBULLETTRAILCONTROLLER_H_
#define _ENEMYBULLETTRAILCONTROLLER_H_

#include "main.h"
#include "Framework\BaseParticleController.h"

/**************************************
マクロ定義
***************************************/

/**************************************
クラス定義
***************************************/
class EnemyBulletTrailController : public BaseParticleController
{
public:
	void Init();
	void Emit();
};

#endif