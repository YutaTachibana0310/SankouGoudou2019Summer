//=====================================
//
//エネミーバレットチャージ処理[EnemyBulletCharge.cpp]
//Author:GP12A332 21 立花雄太
//
//=====================================
#include "EnemyBulletCharge.h"

/**************************************
マクロ定義
***************************************/
#define ENEMYBULLETCHARGE_POS_RANGE		(10.0f)

/**************************************
EnemyBulletCharge初期化処理
***************************************/
void EnemyBulletCharge::Init()
{
	cntFrame = 0;
	active = true;

	transform.Rotate(0.0f, 0.0f, RandomRangef(0.0f, 360.0f));
	transform.pos.x += RandomRangef(-ENEMYBULLETCHARGE_POS_RANGE, ENEMYBULLETCHARGE_POS_RANGE);
	transform.pos.y += RandomRangef(-ENEMYBULLETCHARGE_POS_RANGE, ENEMYBULLETCHARGE_POS_RANGE);

	lifeFrame = 30;
}

/**************************************
EnemyBulletCharge更新処理
***************************************/
void EnemyBulletCharge::Update()
{
	cntFrame++;

	float t = (float)cntFrame / lifeFrame;
	Animation(t);

	if (cntFrame == lifeFrame)
	{
		active = false;
	}
}

/**************************************
EnemyBulletChargeEmitter初期化処理
***************************************/
void EnemyBulletChargeEmitter::Init()
{
	cntFrame = 0;
	active = true;
	transform.scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	duration = 90;
}

/**************************************
EnemyBulletChargeEmitter更新処理
***************************************/
void EnemyBulletChargeEmitter::Update()
{
	cntFrame++;
	
	transform.scale += D3DXVECTOR3(0.05f, 0.05f, 0.05f);
	if (cntFrame == duration)
	{
		active = false;
	}
}