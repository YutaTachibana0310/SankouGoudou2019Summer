//=====================================
//
//�Q�[���X�^�[�g�w�b�_[GameStart.h]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _GAMESTART_H_
#define _GAMESTART_H_

#include "main.h"
#include "IStateMachine.h"
#include "GameScene.h"

/**************************************
�}�N����`
***************************************/

/**************************************
�N���X��`
***************************************/
class GameStart : public IStateMachine<GameScene>
{
public:
	void OnStart(GameScene* entity);
	int OnUpdate(GameScene* entity);
};

#endif