//=====================================
//
//プレイヤームーブヘッダ[PlayerMove.h]
//Author:GP12B332 12 権頭
//
//=====================================
#ifndef _PLAYERMOVE_H_
#define _PLAYERMOVE_H_

#include "main.h"
#include "IStateMachine.h"
#include "player.h"

/**************************************
マクロ定義
***************************************/

/**************************************
構造体定義
***************************************/

/**************************************
クラス定義
***************************************/
class PlayerMove : public IStateMachine<Player> {
public:
	int OnUpdate(Player *entity);
	void OnStart(Player *entity);
	void OnExit(Player * entity);
};

#endif



