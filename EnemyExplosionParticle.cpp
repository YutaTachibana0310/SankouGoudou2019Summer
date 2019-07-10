//=====================================
//
//エネミーエクスプロージョン処理[EnemyExplosionParticle.cpp]
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "EnemyExplosionParticle.h"
#include "Framework\Easing.h"

/**************************************
マクロ定義
***************************************/
#define ENEMYEXPLOSION_MOVEDIR_END	(D3DXVECTOR3(0.0f, -1.0f, 0.0f))

#define ENEMYEXPLOSION_LIFE_MAX		(50)
#define ENEMYEXPLOSION_LIFE_MIN		(20)

#define ENEMYEXPLOSIONEMITTER_DURATION	(5)

/**************************************
EnemyExplosionParticle初期化処理
***************************************/
void EnemyExplosionParticle::Init()
{
	cntFrame = 0;
	active = true;

	//座標をずらす
	const float PosRange = 5.0f;
	transform.pos.x += RandomRangef(-PosRange, PosRange);
	transform.pos.y += RandomRangef(-PosRange, PosRange);
	transform.pos.z += RandomRangef(-PosRange, PosRange);

	//寿命決定
	lifeFrame = RandomRange(ENEMYEXPLOSION_LIFE_MIN, ENEMYEXPLOSION_LIFE_MAX);

	//回転
	transform.Rotate(0.0f, 0.0f, RandomRangef(0.0f, 360.0f));

	//スケール
	transform.scale.x = transform.scale.y = transform.scale.z = RandomRangef(1.0f, 1.5f);
}

/**************************************
EnemyExplosionParticle終了処理
***************************************/
void EnemyExplosionParticle::Uninit()
{
	active = false;
}

/**************************************
EnemyExplosionParticle更新処理
***************************************/
void EnemyExplosionParticle::Update()
{
	cntFrame++;

	//アニメーション
	float t = (float)cntFrame / (float)lifeFrame;
	Animation(t);

	//寿命判定
	if (cntFrame == lifeFrame)
	{
		active = false;
	}

}

/**************************************
EnemyExplosionEmitter初期化処理
***************************************/
void EnemyExplosionEmitter::Init()
{
	active = true;
	cntFrame = 0;
	duration = ENEMYEXPLOSIONEMITTER_DURATION;
}

/**************************************
EnemyExplosionEmitter終了処理
***************************************/
void EnemyExplosionEmitter::Uninit()
{
	active = false;
}

/**************************************
EnemyExplosionPEmitter更新処理
***************************************/
void EnemyExplosionEmitter::Update()
{
	cntFrame++;

	if (cntFrame == duration)
	{
		active = false;
	}
}