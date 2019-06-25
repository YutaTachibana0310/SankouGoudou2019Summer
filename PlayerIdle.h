//=====================================
//
//プレイヤーアイドルヘッダ[PlayerIdle.h]
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _PLAYERIDLE_H_
#define _PLAYERIDLE_H_

#include "main.h"
#include "IStateMachine.h"
#include "Player.h"

/**************************************
マクロ定義
***************************************/

/**************************************
クラス定義
***************************************/
class PlayerIdle : public IStateMachine<Player>
{
public:
	void OnStart(Player *entity);
	void OnUpdate(Player *entity);
	void OnExit(Player *entity);
};

#endif