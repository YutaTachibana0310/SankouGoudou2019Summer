//=====================================
//
//エネミーガイドアロー処理[EnemyGuideArrow.cpp]
//Author:GP12A332 21 立花雄太
//
//=====================================
#include "EnemyGuideArrow.h"
#include "Framework\Easing.h"

/**************************************
マクロ定義
***************************************/
#define ENEMYGUIDEARROW_LIFEFRAME		(60)
#define ENEMYGUIDEARROW_DURATION		(30)

/**************************************
EnemyGuideArrow初期化処理
***************************************/
void EnemyGuideArrow::Init()
{
	cntFrame = 0;
	active = true;

	transform.scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	lifeFrame = ENEMYGUIDEARROW_LIFEFRAME;
}

/**************************************
EnemyGuideArrow更新処理
***************************************/
void EnemyGuideArrow::Update()
{
	static const float InitScale = 1.0f, EndScale = 0.0f;
	cntFrame++;

	float t = (float)cntFrame / lifeFrame;
	transform.scale = Easing<float>::GetEasingValue(t, &InitScale, &EndScale, EasingType::InExponential) * D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	if (cntFrame == lifeFrame)
		active = false;
}

/**************************************
EnemyGuideArrow初期化処理
***************************************/
void EnemyGuideArrowEmitter::Init()
{
	cntFrame = 0;
	active = true;
	duration = ENEMYGUIDEARROW_DURATION;
}

/**************************************
EnemyGuideArrow初期化処理
***************************************/
void EnemyGuideArrowEmitter::Update()
{
	cntFrame++;

	float t = (float)cntFrame / duration;
	transform.pos = Easing<D3DXVECTOR3>::GetEasingValue(t, &start, &end, EasingType::Linear);

	if (cntFrame == duration)
		active = false;
}