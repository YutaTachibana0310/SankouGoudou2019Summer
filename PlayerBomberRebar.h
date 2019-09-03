//=====================================
//
//PlayerBomberRebar.h
//�@�\:�S����ǔ�����{���o�[
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _PLAYERBOMBERREBAR_H_
#define _PLAYERBOMBERREBAR_H_

#include "main.h"
#include "PlayerBomber.h"

/**************************************
�O���錾
***************************************/

/**************************************
�N���X��`
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