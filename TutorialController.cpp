//=====================================
//
//チュートリアルコントローラ処理[TutorialController.cpp]
//Author:GP12A332 21 立花雄太
//
//=====================================
#include "TutorialController.h"
#include "TutorialGuide.h"
#include "masktex.h"

/**************************************
グローバル変数
***************************************/

/**************************************
コンストラクタ
***************************************/
TutorialController::TutorialController() :
	cntFrame(0),
	step(0),
	guide(new TutorialGuide()),
	skip(new Polygon2D())
{
	//座標決定
	const D3DXVECTOR3 Position = D3DXVECTOR3(300.0f, 700.0f, 0.0f);
	guide->transform.pos = Position;
	guide->Set(step);

	//スキップガイド設定
	skip->LoadTexture("data/TEXTURE/Tutorial/skip.png");
	skip->SetSize(240.0f, 30.0f);
	skip->transform.pos = D3DXVECTOR3(SCREEN_WIDTH - 240.0f, SCREEN_HEIGHT - 30.0f, 0.0f);
}

/**************************************
デストラクタ
***************************************/
TutorialController::~TutorialController()
{
	SAFE_DELETE(guide);
	SAFE_DELETE(skip);
}

/**************************************
更新処理
***************************************/
void TutorialController::Update()
{
	guide->Update();

	cntFrame = WrapAround(0, GuideDuration, cntFrame + 1);

	if (cntFrame == 0)
	{
		step++;
		bool isTutorialEnd = !guide->Set(step);
		if (isTutorialEnd)
			SceneChangeFlag(true, Scene::SceneGame);
	}

}

/**************************************
描画処理
***************************************/
void TutorialController::Draw()
{
	guide->Draw();
	skip->Draw();
}
