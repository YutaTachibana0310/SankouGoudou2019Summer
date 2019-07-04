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
#define ENEMYEXPLOSION_SPEED_MAX	(3.0f)
#define ENEMYEXPLOSION_SPEED_MIN	(0.5f)

#define ENEMYEXPLOSION_MOVEDIR_END	(D3DXVECTOR3(0.0f, -1.0f, 0.0f))

#define ENEMYEXPLOSION_LIFE_MAX		(60)
#define ENEMYEXPLOSION_LIFE_MIN		(20)

/**************************************
EnemyExplosionParticle初期化処理
***************************************/
void EnemyExplosionParticle::Init()
{
	cntFrame = 0;
	active = true;

	//移動方向初期化
	initMoveDir.x = RandomRangef(-1.0f, 1.0f);
	initMoveDir.y = RandomRangef(-1.0f, 1.0f);
	initMoveDir.z = RandomRangef(-1.0f, 1.0f);
	D3DXVec3Normalize(&initMoveDir, &initMoveDir);

	//スピード決定
	speed = RandomRangef(ENEMYEXPLOSION_SPEED_MIN, ENEMYEXPLOSION_SPEED_MAX);

	//寿命決定
	lifeFrame = RandomRange(ENEMYEXPLOSION_LIFE_MIN, ENEMYEXPLOSION_SPEED_MAX);
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

	//移動方向に重力っぽい力をかけて移動
	D3DXVECTOR3 moveDir = Easing<D3DXVECTOR3>::GetEasingValue(t, &initMoveDir, &ENEMYEXPLOSION_MOVEDIR_END, EasingType::InCubic);
	transform.pos += moveDir * speed;

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
	duration = 5;
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