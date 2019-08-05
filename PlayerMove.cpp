//=====================================
//
//プレイヤームーブ処理[PlayerMove.cpp]
//Author:GP12B332 12 権頭
//
//=====================================
#include "PlayerMove.h"
#include "Framework/Easing.h"

/**************************************
マクロ定義
***************************************/
#define PLAYER_MOVE_DURATION	(20)

/**************************************
構造体定義
***************************************/

/**************************************
更新処理
***************************************/
int PlayerMove::OnUpdate(Player *entity)
{
	entity->cntFrame++;
	float t = (float)entity->cntFrame / PLAYER_MOVE_DURATION;
	entity->transform.pos = Easing::EaseValue(t, entity->initpos, entity->goalpos, EaseType::OutCubic);

	if (entity->cntFrame == PLAYER_MOVE_DURATION)
	{
		OnExit(entity);
		return STATE_FINISHED;
	}

	return STATE_CONTINUOUS;
}

/**************************************
入場処理
***************************************/
void PlayerMove::OnStart(Player *entity)
{
	//初期化
	entity->cntFrame = 0;
	entity->initpos = entity->transform.pos;
}

/**************************************
退場処理
***************************************/
void PlayerMove::OnExit(Player * entity)
{
}
