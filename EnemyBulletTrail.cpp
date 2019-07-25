//=====================================
//
//エネミーバレットトレイル処理[EnemyBulletTrail.cpp]
//Author:GP12A332 21 立花雄太
//
//=====================================
#include "EnemyBulletTrail.h"

/**************************************
マクロ定義
***************************************/
#define ENEMYBULLETTRAIL_SPEED_MIN	(0.5f)
#define ENEMYBULLETTRAIL_SPEED_MAX	(4.0f)
#define ENEMYBULLETTRAIL_LIFE_MIN	(5)
#define ENEMYBULLETTRAIL_LIFE_MAX	(30)

/**************************************
EnemyBulletTrail初期化処理
***************************************/
void EnemyBulletTrail::Init()
{
	cntFrame = 0;
	active = true;
	speed = RandomRangef(ENEMYBULLETTRAIL_SPEED_MIN, ENEMYBULLETTRAIL_SPEED_MAX);
	lifeFrame = RandomRange(ENEMYBULLETTRAIL_LIFE_MIN, ENEMYBULLETTRAIL_LIFE_MAX);
	transform.Rotate(0.0f, 0.0f, RandomRangef(0.0f, 360.0f));
}

/**************************************
EnemyBulletTrail更新処理
***************************************/
void EnemyBulletTrail::Update()
{
	transform.pos += speed * moveDir;

	cntFrame++;

	float t = (float)cntFrame / (float)lifeFrame;
	Animation(t);

	if (cntFrame == lifeFrame)
	{
		active = false;
	}
}

/**************************************
EnemyBulletTrailEmitter初期化処理
***************************************/
void EnemyBulletTrailEmitter::Init()
{
	prevPos = transform.pos;
	cntFrame = 0;
	active = true;
}

/**************************************
EnemyBulletTrailEmitter更新処理
***************************************/
void EnemyBulletTrailEmitter::Update()
{
	
}