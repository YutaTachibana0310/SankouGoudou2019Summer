//=====================================
//
//エネミーバレットチャージヘッダ[EnemyBulletCharge.h]
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _ENEMYBULLETCHARGE_H_
#define _ENEMYBULLETCHARGE_H_

#include "main.h"
#include "Framework\AnimationParticle.h"
#include "Framework\BaseEmitter.h"

/**************************************
マクロ定義
***************************************/

/**************************************
EnemyBulletChargeクラス
***************************************/
class EnemyBulletCharge : public AnimationParticle
{
public:
	void Init();
	void Update();
};

/**************************************
EnemyBulletChargeEmitterクラス
***************************************/
class EnemyBulletChargeEmitter : public BaseEmitter
{
public:
	void Init();
	void Update();
};

#endif