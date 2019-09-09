//=====================================
//
//プレイヤー墜落処理[PlayerFalldown.cpp]
//Author:GP12A332 21 立花雄太
//
//=====================================
#include "PlayerFalldown.h"
#include "Framework\Easing.h"
#include "Framework\Vector3.h"
#include "PlayerObserver.h"

/**************************************
グローバル変数
***************************************/

/**************************************
入場処理
***************************************/
void PlayerFalldown::OnStart(Player * entity)
{
	entity->ChangeAnim(PlayerAnimID::FallDown);
	entity->cntFrame = 0;
	initPos = entity->transform.pos;
}

/**************************************
更新処理
***************************************/
int PlayerFalldown::OnUpdate(Player * entity)
{
	entity->cntFrame++;

	const float FallDuration = 240;
	float t = entity->cntFrame / FallDuration;
	entity->transform.pos = Easing::EaseValue(t, initPos, initPos + Vector3::Down * 300.0f, EaseType::InSine);

	return StateContinuous;
}
