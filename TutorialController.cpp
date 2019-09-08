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
	step(0)
{
	tutorialContainer.reserve(StepMax);
	for (int i = 0; i < StepMax; i++)
	{
		TutorialGuide *ptr = new TutorialGuide("");

		ptr->transform.pos = D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_CENTER_Y, 0.0f);

		tutorialContainer.push_back(ptr);
	}
}

/**************************************
デストラクタ
***************************************/
TutorialController::~TutorialController()
{
	for (auto&& guide : tutorialContainer)
	{
		SAFE_DELETE(guide);
	}
	tutorialContainer.clear();
}

/**************************************
更新処理
***************************************/
void TutorialController::Update()
{
	if (step >= StepMax)
		return;

	tutorialContainer[step]->Update();

	cntFrame = WrapAround(0, TutorialGuide::LifeFrame, cntFrame + 1);

	if (cntFrame == 0)
	{
		step++;
		if (step == StepMax)
		{
			SceneChangeFlag(true, Scene::SceneGame);
		}
	}

}

/**************************************
描画処理
***************************************/
void TutorialController::Draw()
{
	if (step >= StepMax)
		return;

	tutorialContainer[step]->Draw();
}
