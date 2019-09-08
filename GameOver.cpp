//=====================================
//
//GameOver.cpp
//機能:ゲームオーバー表示
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "GameOver.h"

/**************************************
グローバル変数
***************************************/

/**************************************
コンストラクタ
***************************************/
GameOver::GameOver() :
	cntFrame(0)
{
	LoadTexture("data/TEXTURE/UI/gameOver.png");
	transform.pos = D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_CENTER_Y, 0.0f);
	SetSize(550.0f, 100.0f);
	SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
}

/**************************************
更新処理
***************************************/
void GameOver::Update()
{
	cntFrame++;
	float t = 1.0f * cntFrame / Duration;

	SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, t));
}

/**************************************
グローバル変数
***************************************/
void GameOver::Draw()
{
	Polygon2D::Draw();
}