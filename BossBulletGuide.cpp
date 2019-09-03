//=====================================
//
//ボスバレットガイド処理[BossBulletGuide.cpp]
//Author:GP12A332 21 立花雄太
//
//=====================================
#include "BossBulletGuide.h"
#include "Framework\Easing.h"

/**************************************
グローバル変数
***************************************/

/**************************************
コンストラクタ
***************************************/
BossBulletGuide::BossBulletGuide() :
	Polygon2D(50.0f, 50.0f),
	cntFrame(0),
	Duration(60),
	FadeDuration(10),
	currentState(State::Idle)
{
	LoadTexture("data/TEXTURE/UI/Boss/bulletGuide.png");
}

/**************************************
更新処理
***************************************/
void BossBulletGuide::Update()
{
	if (cntFrame > Duration)
		return;

	cntFrame++;

	if (cntFrame == Duration - FadeDuration)
		currentState = State::Fadeout;
		
	if (currentState == State::Fadein)
	{
		float t = 1.0f *  cntFrame / FadeDuration;
		float alpha = Easing::EaseValue(t, 0.0f,1.0f, EaseType::Linear);
		SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, alpha));
	}
	else if (currentState == State::Fadeout)
	{
		float t = 1.0f - (float)(Duration - cntFrame) / FadeDuration;
		float alpha = Easing::EaseValue(t, 1.0f, 0.0f, EaseType::Linear);
		SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, alpha));
	}
}

/**************************************
セット処理
***************************************/
void BossBulletGuide::Set(const D3DXVECTOR3 & pos, bool isFadein)
{
	transform.pos = pos;
	cntFrame = 0;

	currentState = isFadein ? State::Fadein : State::Fadeout;
}

/**************************************
アクティブ判定
***************************************/
bool BossBulletGuide::IsActive()
{
	return cntFrame <= Duration;
}
