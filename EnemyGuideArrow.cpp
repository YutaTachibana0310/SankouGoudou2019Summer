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
#define ENEMYGUIDEARROW_LIFEFRAME		(45)
#define ENEMYGUIDEARROW_DURATION		(20)

#define ENEMYGUIDEARROW_BASE_VECTOR		(&D3DXVECTOR3(0.0f, 1.0f, 0.0f))

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

	D3DXVECTOR3 diff = end - start;
	D3DXVec3Normalize(&diff, &diff);

	int dir = diff.x < 0 ? 1 : -1;

	transform.rot.z = dir * acosf(D3DXVec3Dot(ENEMYGUIDEARROW_BASE_VECTOR, &diff))               ;
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