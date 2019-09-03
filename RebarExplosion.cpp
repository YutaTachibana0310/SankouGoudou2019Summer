//=====================================
//
//RebarExplosion.cpp
//機能:鉄骨の爆発エフェクト
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "RebarExplosion.h"

/**************************************
グローバル変数
***************************************/

/**************************************
RebarExplosionコンストラクタ
***************************************/
RebarExplosion::RebarExplosion()
{
	SetAnimParameter(&D3DXVECTOR2(8.0f, 8.0f));
}

/**************************************
RebarExplosion初期化処理
***************************************/
void RebarExplosion::Init()
{
	const float PosRange = 10.0f;

	transform.pos.x += RandomRangef(-PosRange, PosRange);
	transform.pos.y += RandomRangef(-PosRange, PosRange);
	transform.pos.z += RandomRangef(-PosRange, PosRange);

	transform.Rotate(0.0f, 0.0f, RandomRangef(0.0f, 360.0f));

	const int LifeMin = 60;
	const int LifeMax = 90;

	cntFrame = 0;
	lifeFrame = RandomRange(LifeMin, LifeMax);
	active = true;
}

/**************************************
RebarExplosion更新処理
***************************************/
void RebarExplosion::Update()
{
	cntFrame++;

	float t = 1.0f * cntFrame / lifeFrame;

	Animation(t);

	if (cntFrame == lifeFrame)
	{
		active = false;
	}
}

/**************************************
RebarExplosionEmitter初期化処理
***************************************/
void RebarExplosionEmitter::Init()
{
	cntFrame = 0;
	duration = 5;
	active = true;
}

/**************************************
RebarExplosionEmitter更新処理
***************************************/
void RebarExplosionEmitter::Update()
{
	cntFrame++;

	if (cntFrame == duration)
	{
		active = false;
	}
}

/**************************************
RebarExplosionController初期化処理
***************************************/
void RebarExplosionController::Init()
{
	MakeUnitBuffer(&D3DXVECTOR2(25.0f, 25.0f), &D3DXVECTOR2(8.0f, 8.0f));
	LoadTexture("data/TEXTURE/Effect/ExplosionFire.png");

	particleContainer.resize(256);
	for (auto&& particle : particleContainer)
	{
		particle = new RebarExplosion();
	}

	emitterContainer.resize(64);
	for (auto&& emitter : emitterContainer)
	{
		emitter = new RebarExplosionEmitter();
	}
}

/**************************************
RearExplosionController放出処理
***************************************/
void RebarExplosionController::Emit()
{
	ForEachEmitter(3, [](BaseEmitter* emitter, BaseParticle* particle)
	{
		particle->transform = emitter->transform;
		particle->Init();
	});
}
