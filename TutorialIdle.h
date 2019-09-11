//=====================================
//
//TutorialIdle.h
//機能:
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _TUTORIALIDLE_H_
#define _TUTORIALIDLE_H_

#include "main.h"
#include "IStateMachine.h"
#include "TutorialScene.h"

/**************************************
前方宣言
***************************************/
class TutorialScene;

/**************************************
クラス定義
***************************************/
class TutorialScene::TutorialIdle : public IStateMachine<TutorialScene>
{
public:
	void OnStart(TutorialScene *entity);
	int OnUpdate(TutorialScene *entity);

};
#endif