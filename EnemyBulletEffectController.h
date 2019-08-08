//=====================================
//
//エネミーバレットエフェクトコントローラヘッダ[EnemyBulletEffectController.h]
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _ENEMYBULLETEFFECTCONTROLLER_H_
#define _ENEMYBULLETEFFECTCONTROLLER_H_

#include "main.h"
#include "Framework\BaseParticleController.h"
#include "LineTrailModel.h"

/**************************************
マクロ定義
***************************************/

/**************************************
クラス定義
***************************************/
class EnemyBulletEffectController : public BaseParticleController
{
public:
	void Init();
	void Emit();
	BaseEmitter* SetEmitter(LineTrailModel model);
};

#endif