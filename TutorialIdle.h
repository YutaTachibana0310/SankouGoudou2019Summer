//=====================================
//
//TutorialIdle.h
//�@�\:
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _TUTORIALIDLE_H_
#define _TUTORIALIDLE_H_

#include "main.h"
#include "IStateMachine.h"
#include "TutorialScene.h"

/**************************************
�O���錾
***************************************/
class TutorialScene;

/**************************************
�N���X��`
***************************************/
class TutorialScene::TutorialIdle : public IStateMachine<TutorialScene>
{
public:
	void OnStart(TutorialScene *entity);
	int OnUpdate(TutorialScene *entity);

};
#endif