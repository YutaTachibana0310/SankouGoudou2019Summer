//=====================================
//
//�{���o�[�V�[�P���X�w�b�_[GameBomberSequence.h]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _GAMEBOMBERSEQUENCE_H_
#define _GAMEBOMBERSEQUENCE_H_

#include "main.h"
#include "IStateMachine.h"
#include "GameScene.h"

/**************************************
�}�N����`
***************************************/

/**************************************
�N���X��`
***************************************/
class GameScene::GameBomberSequence : public IStateMachine<GameScene>
{
	int OnUpdate(GameScene* entity);
	void OnStart(GameScene* entity);

private:
	int cntFrame;
};

#endif