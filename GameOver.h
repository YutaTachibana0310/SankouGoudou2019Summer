//=====================================
//
//GameOver.h
//機能:ゲームオーバー表示
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _GAMEOVER_H_
#define _GAMEOVER_H_

#include "main.h"
#include "Framework\Polygon2D.h"

/**************************************
前方宣言
***************************************/

/**************************************
クラス定義
***************************************/
class GameOver : Polygon2D
{
public:
	GameOver();

	void Update();
	void Draw();
private:
	int cntFrame;

	const int Duration = 120;
};
#endif