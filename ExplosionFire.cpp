//=====================================
//
//エクスプロージョンファイア処理[ExplosionFire.cpp]
//Author:GP12A332 21 立花雄太
//
//=====================================
#include "ExplosionFire.h"

/**************************************
マクロ定義
***************************************/

/**************************************
ExplosionFireコンストラクタ
***************************************/
ExplosionFire::ExplosionFire()
{
	SetAnimParameter(&D3DXVECTOR2(8.0f, 8.0f));
	speed = RandomRangef(2.0f, 5.0f);
	moveDir.x = RandomRangef(-1.0f, 1.0f);
	moveDir.y = RandomRangef(-1.0f, 1.0f);
	moveDir.z = RandomRangef(-1.0f, 1.0f);
	D3DXVec3Normalize(&moveDir, &moveDir);

	lifeFrame = RandomRange(120, 240);
}

/**************************************
ExplosionFire初期化処理
***************************************/
void ExplosionFire::Init()
{
	transform.Rotate(0.0f, 0.0f, RandomRangef(0.0f, 360.0f));

	const float PosRange = 75.0f;
	transform.pos.x += RandomRangef(-PosRange, PosRange);
	transform.pos.y += RandomRangef(-PosRange, PosRange);
	transform.pos.z += RandomRangef(-PosRange, PosRange);

	cntFrame = 0;
	active = true;
}

/**************************************
ExplosionFire更新処理
***************************************/
void ExplosionFire::Update()
{
	cntFrame++;

	float t = (float)cntFrame / lifeFrame;
	Animation(t);

	transform.pos += moveDir * speed;

	if (cntFrame == lifeFrame)
	{
		active = false;
	}
}

/**************************************
ExplosionFireEmitter初期化処理
***************************************/
void ExplosionFireEmitter::Init()
{
	cntFrame = 0;
	duration = 60;
	active = true;
}

/**************************************
ExplosionFireEmitter更新処理
***************************************/
void ExplosionFireEmitter::Update()
{
	cntFrame++;

	if (cntFrame == duration)
	{
		active = false;
	}
}

/**************************************
ExplosionFireController初期化処理
***************************************/
void ExplosionFireController::Init()
{
	MakeUnitBuffer(&D3DXVECTOR2(300.0f, 300.0f), &D3DXVECTOR2(8.0f, 8.0f));
	LoadTexture("data/TEXTURE/Effect/ExplosionFire.png");

	particleContainer.resize(1024);
	for (auto&& particle : particleContainer)
	{
		particle = new ExplosionFire();
	}

	emitterContainer.resize(4);
	for (auto&& emitter : emitterContainer)
	{
		emitter = new ExplosionFireEmitter();
	}
}

/**************************************
ExplosionFireController放出処理
***************************************/
void ExplosionFireController::Emit()
{
	ForEachEmitter(9, [](BaseEmitter* emitter, BaseParticle* particle)
	{
		particle->transform = emitter->transform;
		particle->Init();
	});
}
