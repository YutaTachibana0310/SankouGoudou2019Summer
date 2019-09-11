//=====================================
//
// TutorialController.h
// 機能:チュートリアル管理処理
// Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _TUTORIALCONTROLLER_H_
#define _TUTORIALCONTROLLER_H_

#include "main.h"
#include <vector>

/**************************************
前方宣言
***************************************/
class TutorialGuide;
class Polygon2D;

/**************************************
クラス定義
***************************************/
class TutorialController
{
public:
	TutorialController();
	~TutorialController();

	void Update();
	void Draw();

private:
	int cntFrame;
	int step;
	TutorialGuide *guide;
	Polygon2D *skip;

	const int GuideDuration = 360;
};

#endif