//=====================================
//
//ワーニングテキストヘッダ[WarningText.h]
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _WARNINGTEXT_H_
#define _WARNINGTEXT_H_

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
class WarningText : public Polygon2D
{
public:
	enum Index
	{
		W,
		A,
		R,
		N,
		I,
		G,
		EXCLAMATION,		
	};

	WarningText(Index index);

	void Update();
	void StartAnimation(bool isIn);

private:
	enum State
	{
		In,
		Out,
		Idle
	};

	State currentState;
	int cntFrame;
	float startScale, endScale;

	static const float Size;

	void SetUV(int index);
};
#endif