//=====================================
//
//プレイヤーアイドル処理[PlayerIdle.cpp]
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "PlayerIdle.h"

/**************************************
マクロ定義
***************************************/

/**************************************
構造体定義
***************************************/

/**************************************
グローバル変数
***************************************/

/**************************************
入場処理
***************************************/
void PlayerIdle::OnStart(Player *entity)
{
	entity->cntFrame = 0;
}

/**************************************
更新処理
***************************************/
void PlayerIdle::OnUpdate(Player *entity)
{

}

/**************************************
退場処理
***************************************/
void PlayerIdle::OnExit(Player *entity)
{
	if (callback != NULL)
		callback();
}