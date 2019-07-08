//=====================================
//
//エネミーエクスプロージョンヘッダ[EnemyExplosionParticle.h]
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _ENEMYEXPLOSIONPARTICLE_H_
#define _ENEMYEXPLOSIONPARTICLE_H_

#include "main.h"
#include "Framework\AnimationParticle.h"
#include "Framework\BaseEmitter.h"

/**************************************
マクロ定義
***************************************/

/**************************************
EnemyExplosionParticleクラス
***************************************/
class EnemyExplosionParticle : public AnimationParticle
{
public:
	void Init();
	void Uninit();
	void Update();
};

/**************************************
EnemyExplosionEmitterクラス
***************************************/
class EnemyExplosionEmitter : public BaseEmitter
{
public:
	void Init();
	void Uninit();
	void Update();

};
#endif