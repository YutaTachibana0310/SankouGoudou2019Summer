//=====================================
//
//TutorialBomber.h
//機能:
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _TUTORIALBOMBER_H_
#define _TUTORIALBOMBER_H_

#include "main.h"
#include "IStateMachine.h"
#include "TutorialScene.h"

/**************************************
前方宣言
***************************************/

/**************************************
クラス定義
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