//=====================================
//
//TutorialBG.h
//機能:チュートリアルシーンの背景
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _TUTORIALBG_H_
#define _TUTORIALBG_H_

#include "main.h"
#include "SkyBox.h"

/**************************************
前方宣言
***************************************/
class Polygon2D;

/**************************************
クラス定義
***************************************/
class TutorialBG : public SkyBox
{
public:
	TutorialBG();

	void Draw();
	void Update();

private:
	Polygon2D *polygon;

	static const D3DXVECTOR3 BoxSize;
	static const D3DXVECTOR2 BoxUV;
	static const float ScrollSpeed;
};

#endif