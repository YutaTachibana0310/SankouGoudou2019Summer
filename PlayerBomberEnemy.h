//=====================================
//
//エネミーを追尾するボンバーヘッダ[PlayerBomberEnemy.h]
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _PLAYERBOMBERENEMY_H_
#define _PLAYERBOMBERENEMY_H_

#include "main.h"
#include "PlayerBomber.h"
#include <memory>

/**************************************
前方宣言
***************************************/

/**************************************
クラス定義
***************************************/
class PlayerBomberEnemy : public PlayerBomber
{
	using PlayerBomber::PlayerBomber;
public:
	void Update();
	void Set(std::shared_ptr<Enemy>& target, D3DXVECTOR3 initPos);

private:
	std::weak_ptr<Enemy> target;
};

#endif