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
�v���g�^�C�v�錾
***************************************/
class PlayerWait :IStateMachine<Player> {
public:
	void OnUpdate(Player *entity);
	void OnStart(Player *entity);
	void OnExit(Player *entity);
};


#endif