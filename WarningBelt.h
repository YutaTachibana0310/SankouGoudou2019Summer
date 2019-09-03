//=====================================
//
//ワーニングベルトヘッダ[WarningBelt.h]
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _WARNINGBELT_H_
#define _WARNINGBELT_H_

#include "main.h"
#include "Framework\Polygon2D.h"

/**************************************
前方宣言
***************************************/

/**************************************
マクロ・列挙子定義
***************************************/

/**************************************
クラス定義
***************************************/
class WarningBelt : public Polygon2D
{
	using Polygon2D::Polygon2D;
public:
	WarningBelt(float scrollDir);
	
	void Update();
	void SetFade(bool isFadein);

private:
	enum State
	{
		FadeIn,
		FadeOut,
		Idle
	};

	const float scrollDir;
	int cntFrame;
	float startAlpha, endAlpha;
	State currentState;
};

#endif