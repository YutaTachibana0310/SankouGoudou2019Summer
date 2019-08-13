//=====================================
//
//エネミーエクスプロージョンフレア処理[EnemyExplosionFlare.cpp]
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "EnemyExplosionFlare.h"
#include "Framework\Easing.h"

/**************************************
マクロ定義
***************************************/
#define ENEMYEXPLOSIONFLARE_INIT_OFFSET		(15.0f)
#define ENEMYEXPLOSIONFLARE_LIFE_MIN		(10)
#define ENEMYEXPLOSIONFLARE_LIFE_MAX		(30)

#define ENEMYEXPLOSIONFLARE_MOVEDIR_END		(D3DXVECTOR3(0.0f, -1.0f, 0.0f))

#define ENEMYEXPLOSIONFLARE_SPEED_MIN		(2.8f)
#define ENEMYEXPLOSIONFLARE_SPEED_MAX		(3.5f)

#define ENEMYEXPLOSIONFLARE_EMIT_DURATION	(10)

/**************************************
EnemyExplosionFlare初期化処理
***************************************/
void EnemyExplosionFlare::Init()
{
	//移動方向初期化
	initMoveDir.x = RandomRangef(-1.0f, 1.0f);
	initMoveDir.y = RandomRangef(-1.0f, 1.0f);
	initMoveDir.z = RandomRangef(-1.0f, 1.0f);
	D3DXVec3Normalize(&initMoveDir, &initMoveDir);

	//移動方向へ初期座標を移動させる
	transform.pos += initMoveDir * ENEMYEXPLOSIONFLARE_INIT_OFFSET;

	//寿命設定、カウンタ初期化
	cntFrame = 0;
	lifeFrame = RandomRange(ENEMYEXPLOSIONFLARE_LIFE_MIN, ENEMYEXPLOSIONFLARE_LIFE_MAX);

	//スピード設定
	speed = RandomRangef(ENEMYEXPLOSIONFLARE_SPEED_MIN, ENEMYEXPLOSIONFLARE_SPEED_MAX);

	//初期スケール保存
	initScale = transform.scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	active = true;
}

/**************************************
EnemyExplosionFlare更新処理
***************************************/
void EnemyExplosionFlare::Update()
{
	cntFrame++;

	//移動方向に重力がかかってるっぽくする
	float t = (float)cntFrame / (float)lifeFrame;
	D3DXVECTOR3 moveDir = Easing::EaseValue(t, initMoveDir, ENEMYEXPLOSIONFLARE_MOVEDIR_END, EaseType::InCubic);

	//移動処理
	transform.pos += moveDir * speed;

	//スケール処理
	transform.scale = Easing::EaseValue(t, initScale, D3DXVECTOR3(0.0f, 0.0f, 0.0f), EaseType::InExpo);

	//寿命判定
	if (cntFrame == lifeFrame)
	{
		active = false;
	}
}

/**************************************
EnemyExplosionFlareEmitter初期化処理
***************************************/
void EnemyExplosionFlareEmitter::Init()
{
	cntFrame = 0;
	duration = ENEMYEXPLOSIONFLARE_EMIT_DURATION;
	active = true;
}

/**************************************
EnemyExplosionFlareEmitter更新処理
***************************************/
void EnemyExplosionFlareEmitter::Update()
{
	cntFrame++;

	//寿命判定
	if (cntFrame == duration)
	{
		active = false;
	}
}