//=====================================
//
//�Q�[���o�g���w�b�_[GameBattle.h]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _GAMEBATTLE_H_
#define _GAMEBATTLE_H_

#include "main.h"
#include "IStateMachine.h"
#include "GameScene.h"

/**************************************
�}�N����`
***************************************/

/**************************************
�N���X��`
***************************************/
class GameScene::GameBattle: public IStateMachine<GameScene>
{
public:
	void OnStart(GameScene* entity);
	int OnUpdate(GameScene* entity);
};

#endif