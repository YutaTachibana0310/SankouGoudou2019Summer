//=====================================
//
//ワーニングUIヘッダ[WarningUI.h]
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _WARNINGUI_H_
#define _WARNINGUI_H_

#include "main.h"
#include <vector>

/**************************************
前方宣言
***************************************/
class WarningBelt;
class WarningText;

/**************************************
マクロ・列挙子定義
***************************************/

/**************************************
クラス定義
***************************************/
class WarningUI
{
public:
	WarningUI();
	~WarningUI();

	void Update();
	void Draw();

	void StartFade(bool isFadein);

private:
	WarningBelt *upperBelt, *lowerBelt;
	std::vector<WarningText*> textContainer;
	std::vector<WarningText*>::iterator itrText;

	bool active;
	int cntFrame;

	void CheckFinish();
	void SetTextIn();

	const int TextSetInterval;
	const int Duration;
};

#endif