//=====================================
//
//チュートリアルガイド処理[TutorialGuide.cpp]
//Author:GP12A332 21 立花雄太
//
//=====================================
#include "TutorialGuide.h"

/**************************************
グローバル変数
***************************************/
const int TutorialGuide::FadeDuration = 20;
const int TutorialGuide::LifeFrame = 300;

/**************************************
コンストラクタ
***************************************/
TutorialGuide::TutorialGuide(const char * TexturePath) :
	cntFrame(0)
{
	LoadTexture(TexturePath);

	const float Width = 400.0;
	const float Height = 200.0f;
	SetSize(Width, Height);
}

/**************************************
更新処理
***************************************/
void TutorialGuide::Update()
{
	cntFrame++;

	if (cntFrame <= FadeDuration)
	{
		float t = 1.0f * cntFrame / FadeDuration;
		SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, t));
	}
	else if (cntFrame >= LifeFrame - FadeDuration)
	{
		float t = 1.0f * (LifeFrame - cntFrame) / FadeDuration;
		SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, t));
	}
}
