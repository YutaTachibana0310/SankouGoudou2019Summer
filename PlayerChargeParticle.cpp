//=====================================
//
//プレイヤーチャージパーティクル処理[PlayerChargeParticle.cpp]
//Author:GP12A332 21 立花雄太
//
//=====================================
#include "PlayerChargeParticle.h"
#include "Framework\Easing.h"

/**************************************
マクロ定義
***************************************/
#define PLAYERCHARGEPARTICLE_LIFE_MIN		(10)
#define PLAYERCHARGEPARTICLE_LIFE_MAX		(40)
#define PLAYERCHARGEPARTICLE_EMIT_DURATION	(50)

#define PLAYERCHARGEPARTICLE_SPEED_MIN		(0.2f)
#define PLAYERCHARGEPARTICLE_SPEED_MAX		(1.0f)

/**************************************
PlayerChargeParticle初期化処理
***************************************/
void PlayerChargeParticle::Init()
{
	active = true;
	cntFrame = 0;

	lifeFrame = RandomRange(PLAYERCHARGEPARTICLE_LIFE_MIN, PLAYERCHARGEPARTICLE_LIFE_MAX);

	speed = RandomRangef(PLAYERCHARGEPARTICLE_SPEED_MIN, PLAYERCHARGEPARTICLE_SPEED_MAX);

	moveDir.x = RandomRangef(-1.0f, 1.0f);
	moveDir.y = RandomRangef(-1.0f, 1.0f);
	moveDir.z = RandomRangef(-1.0f, 1.0f);
	D3DXVec3Normalize(&moveDir, &moveDir);

	transform.pos += moveDir * -speed * (float)lifeFrame * 1.5f;
}

/**************************************
PlayerChargeParticle更新処理
***************************************/
void PlayerChargeParticle::Update()
{
	cntFrame++;

	transform.pos += moveDir * speed;

	float t = (float)cntFrame / lifeFrame;
	transform.scale = Easing::EaseValue(t, 0.0f, 1.0f, EaseType::OutCubic) * D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	if (cntFrame == lifeFrame)
		active = false;
}

/**************************************
PlayerChargeParticleEmitter初期化処理
***************************************/
void PlayerChargeParticleEmitter::Init()
{
	active = true;
	cntFrame = 0;

	duration = PLAYERCHARGEPARTICLE_EMIT_DURATION;
}

/**************************************
PlayerChargeParticleEmitter更新処理
***************************************/
void PlayerChargeParticleEmitter::Update()
{
	cntFrame++;

	if (cntFrame == duration)
		active = false;
}