//=====================================
//
//待機処理[PlayerWait.cpp]
//Author:GP12B332 12 権頭
//
//=====================================
#include "PlayerWait.h"

/**************************************
マクロ定義
***************************************/
#define PLAYERWAIT_DURATION		(180)

/**************************************
構造体定義
***************************************/

/**************************************
プロトタイプ宣言
***************************************/


/*************************************
更新処理
**************************************/
int PlayerWait::OnUpdate(Player *entity)
{
	if (entity->inputInterval == PLAYERWAIT_DURATION)
		return STATE_FINISHED;
	else
		return STATE_CONTINUOUS;
}

/*************************************
入場処理
**************************************/
void PlayerWait::OnStart(Player *entity)
{
	entity->cntFrame = 0;
	entity->inputInterval = 0;

	entity->animation->ChangeAnim(PlayerAnimID::Flying, 1.5f, true);
}

/*************************************
退場処理
**************************************/
void PlayerWait::OnExit(Player *entity)
{

}
