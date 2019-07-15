//=====================================
//
//スコアパーティクル処理[ScoreParticle.cpp]
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "ScoreParticle.h"
#include "Framework\Easing.h"

#include <algorithm>

using namespace std;

/**************************************
マクロ定義
***************************************/
#define SCOREPARTICLE_SIZE			(10.0f)
#define SCOREPARTICLE_NUM_MAX		(256)

#define SCOREPARTICLE_TEX_NAME		("data/TEXTURE/Effect/ScoreParticle.png")
#define SCOREPARTICLE_TEX_DIV_X		(1)
#define SCOREPARTICLE_TEX_DIV_Y		(1)
#define SCOREPARTICLE_ANIM_TIME		(1)

#define SCOREPARTICLE_LIFEFRAME		(40)
#define SCOREPARTICLE_LIFE_RANGE	(10)
#define SCOREPARTICLE_SPEED_INIT	(2.0f)
#define SCOREPARTICLE_SPEED_RANGE	(2.0f)
#define SCOREPARTICLE_SPEED_TIME	(10.0f)

#define SCOREPARTICLE_DURATION		(5)
#define SCOREPARTICLE_EMIT_NUM		(10)

/**************************************
ScoreParticle初期化処理
***************************************/
void ScoreParticle::Init()
{
	cntFrame = 0;
	active = true;

	//移動方向設定
	moveDir.x = RandomRangef(-1.0f, 1.0f);
	moveDir.y = RandomRangef(-1.0f, 1.0f);
	moveDir.z = RandomRangef(-1.0f, 1.0f);

	//寿命。スピード設定
	lifeFrame = SCOREPARTICLE_LIFEFRAME + RandomRange(-SCOREPARTICLE_LIFE_RANGE, SCOREPARTICLE_LIFE_RANGE);
	speed = SCOREPARTICLE_SPEED_INIT + RandomRangef(-SCOREPARTICLE_SPEED_RANGE, SCOREPARTICLE_SPEED_RANGE);
}

/**************************************
ScoreParticle終了処理
***************************************/
void ScoreParticle::Uninit()
{
	active = false;
}

/**************************************
ScoreParticle更新処理処理
***************************************/
void ScoreParticle::Update()
{
	const float EndSpeed = 0.2f;
	const float InitScale = 1.0f, EndScale = 0.0f;

	if (!active)
		return;

	//移動処理
	float tSpeed = (float)cntFrame / (float)SCOREPARTICLE_SPEED_TIME;
	float currentSpeed = Easing<float>::GetEasingValue(tSpeed, &speed, &EndSpeed, EasingType::InExponential);
	transform.pos += moveDir * currentSpeed;

	//スケール処理
	float tScale = (float)cntFrame / (float)lifeFrame;
	float currentScale = Easing<float>::GetEasingValue(tScale, &InitScale, &EndScale, EasingType::OutExponential);
	transform.scale = D3DXVECTOR3(currentScale, currentScale, currentScale);

	//寿命判定
	cntFrame++;
	if (cntFrame > lifeFrame)
	{
		active = false;
	}
}

/**************************************
ScoreParticleEmitterコンストラクタ
***************************************/
ScoreParticleEmitter::ScoreParticleEmitter(D3DXVECTOR3 *pos) : BaseEmitter(pos)
{
	cntFrame = 0;
	duration = SCOREPARTICLE_DURATION;
	active = true;
}

/**************************************
ScoreParticleEmitter初期化処理
***************************************/
void ScoreParticleEmitter::Init()
{
	cntFrame = 0;
	duration = SCOREPARTICLE_DURATION;
	active = true;
}

/**************************************
ScoreParticleEmitter終了処理
***************************************/
void ScoreParticleEmitter::Uninit()
{
	active = false;
}

/**************************************
ScoreParticleEmitter更新処理
***************************************/
void ScoreParticleEmitter::Update()
{
	if (!active)
		return;

	//寿命判定
	cntFrame++;
	if (cntFrame > duration)
	{
		active = false;
	}
}