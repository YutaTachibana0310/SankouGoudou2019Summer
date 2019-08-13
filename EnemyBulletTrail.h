//=====================================
//
//エネミーバレットトレイルヘッダ[EnemyBulletTrail.h]
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _ENEMYBULLETTRAIL_H_
#define _ENEMYBULLETTRAIL_H_

#include "main.h"
#include "Framework\AnimationParticle.h"
#include "Framework\BaseEmitter.h"

/**************************************
EnemyBulletTrailクラス
***************************************/
class EnemyBulletTrail : public AnimationParticle
{
public:
	void Init();
	void Update();

	D3DXVECTOR3 moveDir;
	float speed;
};

/**************************************
EnemyBulletTrailEmitterクラス
***************************************/
class EnemyBulletTrailEmitter : public BaseEmitter
{
public:
	void Init();
	void Update();

	D3DXVECTOR3 prevPos;
};

#endif