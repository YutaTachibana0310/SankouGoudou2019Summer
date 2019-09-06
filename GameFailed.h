//=====================================
//
//GameFailed.h
//�@�\:�Q�[���I�[�o�[�X�e�[�g
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _GAMEFAILED_H_
#define _GAMEFAILED_H_

#include "main.h"
#include "IStateMachine.h"
#include "GameScene.h"

/**************************************
�O���錾
***************************************/

/**************************************
�N���X��`
***************************************/
class GameScene::GameFailed : public IStateMachine<GameScene>
{
public:
	void OnStart(GameScene* entity);
	int OnUpdate(GameScene* entity);

private:
	int cntFrame;

	const int MonotoneDuration = 120;
};

#endif