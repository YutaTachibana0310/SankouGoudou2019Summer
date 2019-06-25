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
void PlayerMove::OnUpdate(Player *entity)
{
	entity->cntFrame++;
	float t = (float)entity->cntFrame / PLAYER_MOVE_DURATION;
	entity->transform.pos = Easing<D3DXVECTOR3>::GetEasingValue(t, &entity->initpos, &entity->goalpos, EasingType::OutCubic);

	if (entity->cntFrame == PLAYER_MOVE_DURATION)
	{
		OnExit(entity);
	}
}

/**************************************
入場処理
***************************************/
void PlayerMove::OnStart(Player *entity)
{
	//初期化
	entity->cntFrame = 0;
	entity->initpos = entity->transform.pos;
	entity->trail->Init(&entity->transform.pos);
}

/**************************************
退場処理
***************************************/
void PlayerMove::OnExit(Player * entity)
{
	entity->trail->Uninit();

	if (callback != NULL)
		callback();
}
