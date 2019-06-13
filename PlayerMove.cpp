//=====================================
//
//プレイヤームーブ処理[PlayerMove.cpp]
//Author:GP12B332 12 権頭
//
//=====================================

#include "PlayerMove.h"
#include "Framework/Easing.h"
#include "PlayerController.h"
/**************************************
マクロ定義
***************************************/

/**************************************
構造体定義
***************************************/

/**************************************
プロトタイプ宣言
***************************************/
void PlayerMove::OnUpdate(Player *entity)
{
	entity->cntFrame++;
	float t = (float)entity->cntFrame / PLAYER_MOVE_TIME;
	entity->pos = Easing<D3DXVECTOR3>::GetEasingValue(t, &entity->initpos, &entity->goalpos, EasingType::InCubic);

	if (entity->cntFrame == PLAYER_MOVE_TIME)
	{
		ChangeState(entity, PlayerState::Wait);
	}
}

void PlayerMove::OnStart(Player *entity)
{
	//初期化
	entity->cntFrame = 0;
	entity->initpos = entity->pos;
}

void PlayerMove::OnExit(Player * entity)
{
	//移動終了	バレット発射
	entity->goalpos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);


}
