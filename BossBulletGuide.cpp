//=====================================
//
//ボスバレットガイド処理[BossBulletGuide.cpp]
//Author:GP12A332 21 立花雄太
//
//=====================================
#include "BossBulletGuide.h"

/**************************************
グローバル変数
***************************************/

/**************************************
コンストラクタ
***************************************/
BossBulletGuide::BossBulletGuide() :
	Polygon2D(50.0f, 50.0f),
	cntFrame(0),
	Duration(60)
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
}

/**************************************
セット処理
***************************************/
void BossBulletGuide::Set(const D3DXVECTOR3 & pos)
{
	transform.pos = pos;
	cntFrame = 0;
}

/**************************************
アクティブ判定
***************************************/
bool BossBulletGuide::IsActive()
{
	return cntFrame <= Duration;
}
