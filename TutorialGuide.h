//=====================================
//
// TutorialGuide.h
// 機能:チュートリアルガイド
// Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _TUTORIALGUIDE_H_
#define _TUTORIALGUIDE_H_

#include "main.h"
#include "Framework\Polygon2D.h"

/**************************************
前方宣言
***************************************/

/**************************************
クラス定義
***************************************/
class TutorialGuide : public Polygon2D
{
public:
	TutorialGuide(const char* TexturePath);

	void Update();

	static const int FadeDuration;
	static const int LifeFrame;

private:
	int cntFrame;
};

#endif