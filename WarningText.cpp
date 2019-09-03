//=====================================
//
//ワーニングテキスト処理[WarningText.cpp]
//Author:GP12A332 21 立花雄太
//
//=====================================
#include "WarningText.h"
#include "Framework\Easing.h"
#include "Framework\Vector3.h"

/**************************************
staticメンバ
***************************************/
const float WarningText::Size = 75.0f;

/**************************************
コンストラクタ
***************************************/
WarningText::WarningText(Index index) :
	Polygon2D(Size, Size),
	currentState(Idle)
{
	SetUV(index);
	LoadTexture("data/TEXTURE/UI/Boss/warningText.png");

	vtxPos[2].y = vtxPos[0].y;
	vtxPos[3].y = vtxPos[1].y;
}

/**************************************
更新処理
***************************************/
void WarningText::Update()
{
	cntFrame++;
	
	const float Duration = 30.0f;
	float t = cntFrame / Duration;
	float scale = Easing::EaseValue(t, startScale, endScale, EaseType::OutCubic);

	if (currentState == State::In)
	{
		vtxPos[2].y = vtxPos[0].y + Size * scale * 2.0f;
		vtxPos[3].y = vtxPos[1].y + Size * scale * 2.0f;
	}
	else
	{
		vtxPos[0].y = vtxPos[2].y - Size * scale * 2.0f;
		vtxPos[1].y = vtxPos[3].y - Size * scale * 2.0f;
	}

	const int OutTiming = 240;
	if (cntFrame == OutTiming)
	{
		StartAnimation(false);
	}
}

/**************************************
アニメ開始処理
***************************************/
void WarningText::StartAnimation(bool isIn)
{
	currentState = isIn ? State::In : State::Out;
	cntFrame = 0;
	startScale = isIn ? 0.0f : 1.0f;
	endScale = 1.0f - startScale;
}

/**************************************
UN設定処理
***************************************/
void WarningText::SetUV(int index)
{
	const int DivX = 4;
	const int DivY = 2;

	int x = index % DivX;
	int y = index / DivX;
	float sizeX = 1.0f / DivX;
	float sizeY = 1.0f / DivY;
	
	Polygon2D::SetUV(x * sizeX, y * sizeY, sizeX, sizeY);
}
