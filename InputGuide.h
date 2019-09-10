//=====================================
//
//InputGuide.h
//機能:入力ガイド表示
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _INPUTGUIDE_H_
#define _INPUTGUIDE_H_

#include "main.h"
#include "Framework\Polygon2D.h"

/**************************************
前方宣言
***************************************/
class LineTrailModel;

/**************************************
クラス定義
***************************************/
class InputGuide : public Polygon2D
{
public:
	InputGuide();

	void Draw();
	void Set(LineTrailModel& model);

private:
	bool active;

};

#endif