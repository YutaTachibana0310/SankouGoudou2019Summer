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
	float t = entity->cntFrame / 120;
	entity->pos = Easing<D3DXVECTOR3>::GetEasingValue(t, &entity->initpos, &PLAYER_INIT_POS, EasingType::OutExponential);

};

/*************************************
初期化
**************************************/
void PlayerReturn::OnStart(Player * entity)
{
	entity->cntFrame = 0;
};
/*************************************
終了処理
**************************************/
void PlayerReturn::OnExit(Player *entity)
{

};
