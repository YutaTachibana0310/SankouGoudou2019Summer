//=====================================
//
// PlayerFalldown.h
// 機能:プレイヤーの墜落処理
// Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _PLAYERFALLDOWN_H_
#define _PLAYERFALLDOWN_H_

#include "main.h"
#include "IStateMachine.h"
#include "Player.h"

/**************************************
前方宣言
***************************************/

/**************************************
クラス定義
***************************************/
class PlayerFalldown : public IStateMachine<Player>
{
public:
	void OnStart(Player* entity);
	int OnUpdate(Player* entity);

private:
	D3DXVECTOR3 initPos;

}; 
#endif