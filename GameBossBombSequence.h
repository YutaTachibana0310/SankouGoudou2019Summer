//=====================================
//
//�{�X�o�g���{���o�[�V�[�P���X�w�b�_[GameBossBombSequence.h]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _GAMEBOSSBOMBSEQUENCE_H_
#define _GAMEBOSSBOMBSEQUENCE_H_

#include "main.h"
#include "IStateMachine.h"
#include "GameScene.h"

/**************************************
�O���錾
***************************************/

/**************************************
�N���X��`
***************************************/
class GameScene::GameBossBombSequence : public IStateMachine<GameScene>
{
public:
	void OnStart(GameScene* entity);
	int OnUpdate(GameScene* entity);

private:
	int cntFrame;
};
#endif