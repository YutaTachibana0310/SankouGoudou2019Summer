//=====================================
//
//待機処理[PlayerWait.cpp]
//Author:GP12B332 12 権頭
//
//=====================================

#include "PlayerWait.h"
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
void PlayerWait::OnUpdate(Player *entity)
{
	////entity->cntFrame++;
	//
	////if (entity->cntFrame < 180)
	////{
	//	ChangeState(entity, PlayerState::Wait);
	////}

}

/*************************************
初期化処理
**************************************/
void PlayerWait::OnStart(Player *entity)
{
	entity->cntFrame = 0;
}
/*************************************
終了処理
**************************************/
void PlayerWait::OnExit(Player *entity)
{

}
