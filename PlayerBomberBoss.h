//=====================================
//
//PlayerBomberBoss.h
//機能:ボスを追尾するボンバー
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _PLAYERBOMERBOSS_H_
#define _PLAYERBOMERBOSS_H_

#include "main.h"
#include "PlayerBomber.h"

/**************************************
前方宣言
***************************************/

/**************************************
クラス定義
***************************************/
class PlayerBomberBoss : public PlayerBomber
{
	using PlayerBomber::PlayerBomber;
public:
	void Update();
	void Set(std::shared_ptr<BossEnemyModel>& target, D3DXVECTOR3 initPos);

private:
	std::weak_ptr<BossEnemyModel> target;
};

#endif