//=====================================
//
//TutorialBomber.h
//�@�\:
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _TUTORIALBOMBER_H_
#define _TUTORIALBOMBER_H_

#include "main.h"
#include "IStateMachine.h"
#include "TutorialScene.h"

/**************************************
�O���錾
***************************************/

/**************************************
�N���X��`
***************************************/
class TutorialScene::TutorialBomber : public IStateMachine<TutorialScene>
{
public:
	void OnStart(TutorialScene *entity);
	int OnUpdate(TutorialScene* entity);

private:
	int cntFrame;
};
#endif