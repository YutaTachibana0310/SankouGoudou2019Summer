//=====================================
//
//エネミーワープホール処理[EnemyWarpHole.cpp]
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "EnemyWarpHole.h"

/**************************************
マクロ定義
***************************************/

/**************************************
EnemyWarpHoleコンストラクタ
***************************************/
EnemyWarpHole::EnemyWarpHole()
{
	active = false;
}

/**************************************
EnemyWarpHoleデストラクタ
***************************************/
EnemyWarpHole::~EnemyWarpHole()
{

}

/**************************************
EnemyWarpHole初期化処理
***************************************/
void EnemyWarpHole::Init()
{
	cntFrame = 0;
	lifeFrame = RandomRange(30, 100);
	active = true;

	const float PosRange = 5.0f;
	transform.pos.x += RandomRangef(-PosRange, PosRange);
	transform.pos.y += RandomRangef(-PosRange, PosRange);
	transform.pos.z += RandomRangef(-PosRange, PosRange);
}

/**************************************
EnemyWarpHole更新処理
***************************************/
void EnemyWarpHole::Update()
{
	cntFrame++;
	transform.Rotate(0.0f, 0.0f, 10.0f);

	float t = 1.0f - (float)cntFrame / (float)lifeFrame;
	Animation(t);

	if (cntFrame == lifeFrame)
		Uninit();
}

/**************************************
EnemyWarpHoleEmitterコンストラクタ
***************************************/
EnemyWarpHoleEmitter::EnemyWarpHoleEmitter()
{
	active = false;
}

/**************************************
EnemyWarpHoleEmitterデストラクタ
***************************************/
EnemyWarpHoleEmitter::~EnemyWarpHoleEmitter()
{

}

/**************************************
EnemyWarpHoleEmitter初期化処理
***************************************/
void EnemyWarpHoleEmitter::Init()
{
	cntFrame = 0;
	duration = RandomRange(10, 20);
	active = true;
}

/**************************************
EnemyWarpHoleEmitter更新処理
***************************************/
void EnemyWarpHoleEmitter::Update()
{
	cntFrame++;

	if (cntFrame == duration)
		Uninit();
}