//=====================================
//
//エネミーバレットファイア処理[EnemyBulletFire.cpp]
//Author:GP12A332 21 立花雄太
//
//=====================================
#include "EnemyBulletFire.h"
#include "Framework\Easing.h"

/**************************************
マクロ定義
***************************************/
#define ENEMYBULLETFIRE_LIFE_MIN	(10)
#define ENEMYBULLETFIRE_LIFE_MAX	(30)

#define ENEMYBULLETFIRE_SPEED_MAX	(10.0f)
#define ENEMYBULLETFIRE_SPEED_MIN	(5.0f)

/**************************************
EnemyBulletFire初期化処理
***************************************/
void EnemyBulletFire::Init()
{
	cntFrame = 0;
	active = true;

	lifeFrame = RandomRange(ENEMYBULLETFIRE_LIFE_MIN, ENEMYBULLETFIRE_LIFE_MAX);

	moveDir.x = RandomRangef(-1.0f, 1.0f);
	moveDir.y = RandomRangef(-1.0f, 1.0f);
	moveDir.z = 1.0f;
	D3DXVec3Normalize(&moveDir, &moveDir);

	speed = RandomRangef(ENEMYBULLETFIRE_SPEED_MIN, ENEMYBULLETFIRE_SPEED_MAX);
}

/**************************************
EnemyBulletFire更新処理
***************************************/
void EnemyBulletFire::Update()
{
	static const float EndSpeed = 0.0f;
	static const float InitScale = 1.0f;
	static const float EndScale = 0.0f;

	cntFrame++;
	float t = (float)cntFrame / lifeFrame;

	
	float currentSpeed = Easing<float>::GetEasingValue(t, &speed, &EndSpeed, EasingType::OutCubic);
	transform.pos += moveDir * currentSpeed;

	transform.scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f) * Easing<float>::GetEasingValue(t, &InitScale, &EndScale, EasingType::InExponential);

	if (cntFrame == lifeFrame)
		active = false;
}

/**************************************
EnemyBulletFireEmitter初期化処理
***************************************/
void EnemyBulletFireEmitter::Init()
{
	cntFrame = 0;
	active = true;

	duration = 5;
}

/**************************************
EnemyBulletFireEmitter更新処理
***************************************/
void EnemyBulletFireEmitter::Update()
{
	cntFrame++;

	if (cntFrame == duration)
		active = false;
}