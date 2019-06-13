//=====================================
//
//プレイヤームーブ処理[PlayerMove.cpp]
//Author:GP12B332 12 権頭
//
//=====================================

#include "PlayerReturn.h"
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


/*************************************
更新処理
**************************************/
void PlayerReturn::OnUpdate(Player *entity)
{
	
	float t = (float)entity->cntFrame / PLAYER_RETURN_TIME;
	entity->cntFrame++;
	entity->pos = Easing<D3DXVECTOR3>::GetEasingValue(t, &entity->initpos, &PLAYER_CENTER, EasingType::OutExponential);
	
	if (entity->cntFrame == PLAYER_RETURN_TIME)
	{
		ChangeState(entity, PlayerState::Wait);
	}
};

/*************************************
初期化
**************************************/
void PlayerReturn::OnStart(Player * entity)
{
	entity->cntFrame = 0;
	entity->initpos = entity->pos;

};
/*************************************
終了処理
**************************************/
void PlayerReturn::OnExit(Player *entity)
{

};
