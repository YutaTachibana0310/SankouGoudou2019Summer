//=====================================
//
//�v���C���[���^�[���w�b�_[PlayerReturn.h]
//Author:GP12B332 12 ����
//
//=====================================
#ifndef _PLAYERRETURN_H_
#define _PLAYERRETURN_H_

#include "main.h"
#include "IStateMachine.h"
#include "player.h"

/**************************************
�}�N����`
***************************************/

/**************************************
�\���̒�`
***************************************/

/**************************************
�N���X��`
***************************************/
class PlayerReturn :public IStateMachine<Player> {
public:
	int OnUpdate(Player *entity);
	void OnStart(Player *entity);
	void OnExit(Player *entity);
};


#endif