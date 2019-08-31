//=====================================
//
//ボスバレットガイドヘッダ[BossBulletGuide.h]
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _BOSSBULLETGUIDE_H_
#define _BOSSBULLETGUIDE_H_

#include "main.h"
#include "Framework\Polygon2D.h"

/**************************************
前方宣言
***************************************/

/**************************************
クラス定義
***************************************/
class BossBulletGuide : public Polygon2D
{
public:
	BossBulletGuide();

	void Update();
	void Set(const D3DXVECTOR3& pos, bool isFadein = true);
	bool IsActive();

private:
	enum State
	{
		Fadein,
		Fadeout,
		Idle
	};

	int cntFrame;
	const int Duration;
	State currentState;
	const int FadeDuration;
};

#endif