//=====================================
//
//�v���C���[�A�C�h���w�b�_[PlayerIdle.h]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _PLAYERIDLE_H_
#define _PLAYERIDLE_H_

#include "main.h"
#include "IStateMachine.h"
#include "Player.h"

/**************************************
�}�N����`
***************************************/

/**************************************
�N���X��`
***************************************/
class PlayerIdle : public IStateMachine<Player>
{
public:
	void OnStart(Player *entity);
	void OnUpdate(Player *entity);
	void OnExit(Player *entity);
};

#endif