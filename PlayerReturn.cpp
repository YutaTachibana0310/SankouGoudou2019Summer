//=====================================
//
//プレイヤームーブ処理[PlayerMove.cpp]
//Author:GP12B332 12 権頭
//
//=====================================
#include "PlayerReturn.h"
#include "Framework/Easing.h"

/**************************************
マクロ定義
***************************************/
#define PLAYER_RETURN_DURATION		(20)

/**************************************
構造体定義
***************************************/

/**************************************
プロトタイプ宣言
***************************************/


/*************************************
更新処理
**************************************/
void PlayerReturn::OnUpdate(Player *entity)
{
	float t = (float)entity->cntFrame / PLAYER_RETURN_DURATION;
	entity->cntFrame++;
	entity->transform.pos = Easing<D3DXVECTOR3>::GetEasingValue(t, &entity->initpos, &entity->goalpos, EasingType::OutCubic);
	
	if (entity->cntFrame == PLAYER_RETURN_DURATION)
	{
		OnExit(entity);
	}
};

/*************************************
入場処理
**************************************/
void PlayerReturn::OnStart(Player * entity)
{
	entity->cntFrame = 0;
	entity->initpos = entity->transform.pos;
	entity->goalpos = D3DXVECTOR3(0.0f, -20.0f, 0.0f);
};

/*************************************
退場処理
**************************************/
void PlayerReturn::OnExit(Player *entity)
{
	if (callback != NULL)
		callback();
};
