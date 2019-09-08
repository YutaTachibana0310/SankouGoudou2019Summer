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

/**************************************
前方宣言
***************************************/
class TutorialBG;
class GameSceneUIManager;
class PlayerObserver;
class TutorialController;

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

private:
	TutorialBG * bg;
	GameSceneUIManager* container;
	PlayerObserver *playerObserver;
	TutorialController *controller;

};

#endif