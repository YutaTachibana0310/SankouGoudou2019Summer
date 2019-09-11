//=====================================
//
//TutorialScene.h
//機能:チュートリアルシーン
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _TUTORIALSCENE_H_
#define _TUTORIALSCENE_H_

#include "main.h"
#include "IStateScene.h"
#include "IStateMachine.h"

#include <vector>

/**************************************
前方宣言
***************************************/
class TutorialBG;
class GameSceneUIManager;
class PlayerObserver;
class TutorialController;
class TutorialEnemyController;
class Polygon2D;

/**************************************
クラス定義
***************************************/
class TutorialScene : public IStateScene
{
public:
	void Init() override;
	void Uninit() override;
	void Update(HWND hWnd) override;
	void Draw() override;

	enum State
	{
		Idle,
		Bomber,
		Max
	};

private:
	TutorialBG * bg;
	GameSceneUIManager* container;
	PlayerObserver *playerObserver;
	TutorialController *controller;
	TutorialEnemyController *enemyController;

	std::vector<IStateMachine<TutorialScene>*> fsm;
	State current;

	bool useDarkMask;
	Polygon2D *darkMask;

	bool ShouldFireBomber();

	//ステートクラス
	class TutorialIdle;
	class TutorialBomber;
};

#endif