//=====================================
//
//PlayerBomberRebar.h
//機能:鉄骨を追尾するボンバー
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _PLAYERBOMBERREBAR_H_
#define _PLAYERBOMBERREBAR_H_

#include "main.h"
#include "PlayerBomber.h"

/**************************************
前方宣言
***************************************/

/**************************************
クラス定義
***************************************/
class PlayerBomberRebar : public PlayerBomber
{
	using PlayerBomber::PlayerBomber;
public:
	void Update();
	void Set(std::shared_ptr<RebarObstacle>& target, D3DXVECTOR3 initPos);

private:
	std::weak_ptr<RebarObstacle> target;
};

#endif