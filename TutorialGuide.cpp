//=====================================
//
//チュートリアルガイド処理[TutorialGuide.cpp]
//Author:GP12A332 21 立花雄太
//
//=====================================
#include "TutorialGuide.h"
#include "Framework\ResourceManager.h"

/**************************************
グローバル変数
***************************************/
const int TutorialGuide::FadeDuration = 30;
const int TutorialGuide::LifeFrame = 300;

/**************************************
コンストラクタ
***************************************/
TutorialGuide::TutorialGuide() :
	cntFrame(LifeFrame)
{
	//ポリゴンサイズ設定
	const float AspectRatio = 3.75f;
	const float Height = 65.0f;
	const float Width = Height * AspectRatio;
	SetSize(Width, Height);

	//テクスチャ名
	const char* TexturePath[TutorialStep::Max] = {
		"data/TEXTURE/Tutorial/tutorialstart.png",
		"data/TEXTURE/Tutorial/playermove.png",
		"data/TEXTURE/Tutorial/movebutton.png",
		"data/TEXTURE/Tutorial/comboreset.png",
		"data/TEXTURE/Tutorial/bombstock.png",
		"data/TEXTURE/Tutorial/firebomber.png",
		"data/TEXTURE/Tutorial/tutorialend.png"
	};

	//テクスチャ読み込み
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	textureContainer.resize(TutorialStep::Max, NULL);
	for (int i = 0; i < TutorialStep::Max; i++)
	{
		D3DXCreateTextureFromFile(pDevice, (LPCSTR)TexturePath[i], &textureContainer[i]);
	}
}

/**************************************
更新処理
***************************************/
void TutorialGuide::Update()
{
	if (cntFrame > LifeFrame)
		return;

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

/**************************************
描画処理
***************************************/
void TutorialGuide::Draw()
{
	if (cntFrame > LifeFrame)
		return;

	Polygon2D::Draw();
}

/**************************************
セット処理
***************************************/
bool TutorialGuide::Set(int step)
{
	if (step >= TutorialStep::Max)
		return false;

	SetTexture(textureContainer[step]);
	cntFrame = 0;

	return true;
}
