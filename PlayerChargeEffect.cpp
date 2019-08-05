//=====================================
//
//プレイヤーチャージエフェクト処理[PlayerChargeEffect.cpp]
//Author:GP12A332 21 立花雄太
//
//=====================================
#include "PlayerChargeEffect.h"

/**************************************
マクロ定義
***************************************/
#define PLAYERCHARGEEFFECT_POS_RANGE		(2.0f)
#define PLAYERCHARGEEFFECT_LIFE_MIN			(20)
#define PLAYERCHARGEEFFECT_LIFE_MAX			(60)
#define PLAYERCHARGEEFFECT_EMIT_DURATION	(70)

/**************************************
PlayerChargeEffect初期化処理
***************************************/
void PlayerChargeEffect::Init()
{
	active = true;
	cntFrame = 0;

	transform.Rotate(0.0f, 0.0f, RandomRangef(0.0f, 360.0f));

	transform.pos.x += transform.scale.x * RandomRangef(-PLAYERCHARGEEFFECT_POS_RANGE, PLAYERCHARGEEFFECT_POS_RANGE);
	transform.pos.y += transform.scale.y * RandomRangef(-PLAYERCHARGEEFFECT_POS_RANGE, PLAYERCHARGEEFFECT_POS_RANGE);
	transform.pos.z += transform.scale.z * RandomRangef(-PLAYERCHARGEEFFECT_POS_RANGE, PLAYERCHARGEEFFECT_POS_RANGE);

	lifeFrame = RandomRange(PLAYERCHARGEEFFECT_LIFE_MIN, PLAYERCHARGEEFFECT_LIFE_MAX);
}

/**************************************
PlayerChargeEffect更新処理
***************************************/
void PlayerChargeEffect::Update()
{
	cntFrame++;

	float t = (float)cntFrame / lifeFrame;
	Animation(t);

	if (cntFrame == lifeFrame)
		active = false;
}

/**************************************
PlayerChargeEffectEmitter初期化処理
***************************************/
void PlayerChargeEffectEmitter::Init()
{
	active = true;
	cntFrame = 0;
	duration = PLAYERCHARGEEFFECT_EMIT_DURATION;
}

/**************************************
PlayerChargeEffectEmitter更新処理
***************************************/
void PlayerChargeEffectEmitter::Update()
{
	cntFrame++;
	
	if (cntFrame == PLAYERCHARGEEFFECT_EMIT_DURATION)
		active = false;
}