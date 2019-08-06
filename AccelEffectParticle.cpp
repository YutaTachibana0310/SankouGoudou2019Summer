//=====================================
//
//アクセルエフェクトパーティクル処理[AccelEffectParticle.cpp]
//Author:GP12A332 21 立花雄太
//
//=====================================
#include "AccelEffectParticle.h"
#include "Framework\Easing.h"

/**************************************
マクロ定義
***************************************/
#define ACCELEFFECT_LIFEFRAME		(20)
#define ACCELEFFECT_SCALE			(5.0f)
#define ACCELEFFECT_POS_OFFSET		(3.0f)
#define ACCELEFFECT_SPEED			(10.0f)

/**************************************
AccelEffectParticle初期化処理
***************************************/
void AccelEffectParticle::Init()
{
	cntFrame = 0;
	active = true;

	//移動方向決定
	moveDir.x = RandomRangef(-1.0f, 1.0f);
	moveDir.y = RandomRangef(-1.0f, 1.0f);
	moveDir.z = -1.0f;
	D3DXVec3Normalize(&moveDir, &moveDir);

	//スケール決定
	baseScale = D3DXVECTOR3(fabsf(moveDir.x), fabsf(moveDir.y), 0.0f);
	D3DXVec3Normalize(&baseScale, &baseScale);
	baseScale.z = 1.0f;

	//座標オフセット
	transform.pos += moveDir * ACCELEFFECT_POS_OFFSET;

	//寿命決定
	lifeFrame = ACCELEFFECT_LIFEFRAME;
}

/**************************************
AccelEffectParticle更新処理
***************************************/
void AccelEffectParticle::Update()
{
	cntFrame++;

	//移動
	transform.pos += moveDir * ACCELEFFECT_SPEED;

	//スケールイージング
	float t = (float)cntFrame / lifeFrame;
	transform.scale = Easing::EaseValue(t, 1.0f, 0.0f, EaseType::InCubic) * baseScale;

	if (cntFrame == lifeFrame)
		active = false;

}

/**************************************
AccelEffectParticleEmitter初期化処理
***************************************/
void AccelEffectParticleEmitter::Init()
{
	cntFrame = 0;
	duration = 5;
	active = true;
}

/**************************************
AccelEffectParticleEmitter更新処理
**************************************/
void AccelEffectParticleEmitter::Update()
{
	cntFrame++;

	if (cntFrame == duration)
		active = false;
}