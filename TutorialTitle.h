//=====================================
//
//TutorialTitle.h
//機能:
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _TUTORIALTITLE_H_
#define _TUTORIALTITLE_H_

#include "main.h"
#include "Framework\Polygon2D.h"

/**************************************
前方宣言
***************************************/

/**************************************
クラス定義
***************************************/
class TutorialTitle : public Polygon2D
{
public:
	TutorialTitle();

	void Update();

	static const int FadeInDuration;
	static const int ViewDuration;
	static const int MoveDuration;
	static const int FadeOutDuration;

private:
	int cntFrame;
};
#endif