//=====================================
//
//�G�l�~�[��ǔ�����{���o�[�w�b�_[PlayerBomberEnemy.h]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _PLAYERBOMBERENEMY_H_
#define _PLAYERBOMBERENEMY_H_

#include "main.h"
#include "PlayerBomber.h"
#include <memory>

/**************************************
�O���錾
***************************************/

/**************************************
�N���X��`
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