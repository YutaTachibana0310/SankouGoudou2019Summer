//=====================================
//
//エネミーバレットエフェクト処理[EnemyBulletEffect.cpp]
//Author:GP12A332 21 立花雄太
//
//=====================================
#include "EnemyBulletEffect.h"

/**************************************
マクロ定義
***************************************/
#define ENEMYBULLETEFFECT_LIFE_MIN	(10)
#define ENEMYBULLETEFFECT_LIFE_MAX	(40)

#define ENEMYBULLETEFFECT_DURATION	(120)

/**************************************
EnemyBulletEffect初期化処理
***************************************/
void EnemyBulletEffect::Init()
{
	cntFrame = 0;
	lifeFrame = RandomRange(ENEMYBULLETEFFECT_LIFE_MIN, ENEMYBULLETEFFECT_LIFE_MAX);
	active = true;
}

/**************************************
EnemyBulletEffect更新処理
***************************************/
void EnemyBulletEffect::Update()
{
	cntFrame++;

	float t = (float)cntFrame / (float)lifeFrame;
	Animation(t);

	if (cntFrame == lifeFrame)
		active = false;
}

/**************************************
EnemyBulletEffectEmitter初期化処理
***************************************/
void EnemyBulletEffectEmitter::Init()
{
	cntFrame = 0;
	duration = ENEMYBULLETEFFECT_DURATION;
	active = true;
}

/**************************************
EnemyBulletEffectEmitter更新処理
***************************************/
void EnemyBulletEffectEmitter::Update()
{
	cntFrame++;

	if (cntFrame == duration)
		active = false;
}