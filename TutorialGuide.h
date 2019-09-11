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
#include <vector>

/**************************************
前方宣言
***************************************/

/**************************************
クラス定義
***************************************/
class TutorialGuide : public Polygon2D
{
public:
	//チュートリアルのステップ定義
	enum TutorialStep
	{
		MoveButton,
		ComboReset,
		BombStock,
		FireBomber,
		TutorialEnd,
		Max
	};

	TutorialGuide();

	void Update();
	void Draw();

	bool Set(int step);

	static const int FadeDuration;
	static const int LifeFrame;
	
private:
	int cntFrame;
	std::vector<LPDIRECT3DTEXTURE9> textureContainer;
};

#endif