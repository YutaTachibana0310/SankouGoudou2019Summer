//=====================================
//
//�ҋ@�w�b�_[PlayerWait.h]
//Author:GP12B332 12 ����
//
//=====================================
#ifndef _PLAYERWAIT_H_
#define _PLAYERWAIT_H_

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
class PlayerWait :public IStateMachine<Player> {
public:
	int OnUpdate(Player *entity);
	void OnStart(Player *entity);
	void OnExit(Player *entity);
};


#endif