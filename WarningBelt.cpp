//=====================================
//
//ワーニングベルト処理[WarningBelt.cpp]
//Author:GP12A332 21 立花雄太
//
//=====================================
#include "WarningBelt.h"
#include "Framework\Easing.h"

/**************************************
マクロ定義
***************************************/

/**************************************
クラス定義
***************************************/
WarningBelt::WarningBelt(float scrollDir) :
	Polygon2D(SCREEN_WIDTH / 2.0f, 100.0f, 10.0f, 1.0f),
	scrollDir(scrollDir),
	currentState(State::Idle)
{
	LoadTexture("data/TEXTURE/UI/Boss/warningBelt.png");
}

/**************************************
クラス定義
***************************************/
void WarningBelt::Update()
{
	const float ScrollSpeed = 0.03f;

	for (int i = 0; i < NUM_VERTEX; i++)
	{
		vtxWk[i].tex.x += scrollDir *  ScrollSpeed;
	}

	if (currentState != Idle)
	{
		const float FadeDuration = 30;
		cntFrame++;
		float t = cntFrame / FadeDuration;
		float alpha = Easing::EaseValue(t, startAlpha, endAlpha, EaseType::Linear);
		SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, alpha));
	}
}

/**************************************
フェード設定処理
***************************************/
void WarningBelt::SetFade(bool isFadein)
{
	currentState = isFadein ? State::FadeIn : State::FadeOut;
	cntFrame = 0;
	startAlpha = isFadein ? 0.0f : 1.0f;
	endAlpha = 1.0f - startAlpha;
}
