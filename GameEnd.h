//=====================================
//
//�Q�[���G���h�w�b�_[GameEnd.h]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _GAMEEND_H_
#define _GAMEEND_H_

#include "main.h"
#include "IStateMachine.h"
#include "GameScene.h"

/**************************************
�}�N����`
***************************************/

/**************************************
�N���X��`
***************************************/
class GameEnd : public IStateMachine<GameScene>
{
public:
	void OnStart(GameScene *entity);
	int OnUpdate(GameScene *entity);
};

#endif