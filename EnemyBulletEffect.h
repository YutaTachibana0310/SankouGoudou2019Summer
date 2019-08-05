//=====================================
//
//エネミーバレットエフェクトヘッダ[EnemyBulletEffect.h]
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _ENEMYBULLETEFFECT_H_
#define _ENEMYBULLETEFFECT_H_

#include "main.h"
#include "Framework\AnimationParticle.h"
#include "Framework\BaseEmitter.h"

/**************************************
マクロ定義
***************************************/

/**************************************
EnemyBulletEffectクラス
***************************************/
class EnemyBulletEffect : public AnimationParticle
{
public:
	void Init();
	void Update();
};

/**************************************
EnemyBulletEffectEmitterクラス
***************************************/
class EnemyBulletEffectEmitter : public BaseEmitter
{
public:
	void Init();
	void Update();
	
	D3DXVECTOR3 edgeR, edgeL;
};

#endif