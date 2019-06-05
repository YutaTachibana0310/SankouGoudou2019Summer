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

/**************************************
構造体定義
***************************************/

/**************************************
プロトタイプ宣言
***************************************/
void PlayerMove::OnUpdate(Player *entity)
{
	float t = (float)entity->cntFrame / 120;
	entity->pos = Easing<D3DXVECTOR3>::GetEasingValue(t, &entity->initpos, &entity->goalpos, EasingType::InCubic);
	
}

void PlayerMove::OnStart(Player *entity)
{
	//初期化
	entity->cntFrame = 0;
	entity->goalpos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	
}

void PlayerMove::OnExit(Player * entity)
{
	//移動終了	バレット発射


}
