//=====================================
//
//�v���C���[���[�u�w�b�_[PlayerMove.h]
//Author:GP12B332 12 ����
//
//=====================================
#ifndef _PLAYERMOVE_H_
#define _PLAYERMOVE_H_

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

class PlayerMove : public IStateMachine<Player> {
public:
	void OnUpdate(Player *entity);
	void OnStart(Player *entity);
	void OnExit(Player * entity);
};

#endif



