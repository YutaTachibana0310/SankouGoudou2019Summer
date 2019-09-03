//=====================================
//
//PlayerBomberBoss.h
//�@�\:�{�X��ǔ�����{���o�[
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _PLAYERBOMERBOSS_H_
#define _PLAYERBOMERBOSS_H_

#include "main.h"
#include "PlayerBomber.h"

/**************************************
�O���錾
***************************************/

/**************************************
�N���X��`
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