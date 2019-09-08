//=====================================
//
//�`���[�g���A���R���g���[������[TutorialController.cpp]
//Author:GP12A332 21 ���ԗY��
//
//=====================================
#include "TutorialController.h"
#include "TutorialGuide.h"
#include "masktex.h"

/**************************************
�O���[�o���ϐ�
***************************************/

/**************************************
�R���X�g���N�^
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
�f�X�g���N�^
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
�X�V����
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
�`�揈��
***************************************/
void TutorialController::Draw()
{
	if (step >= StepMax)
		return;

	tutorialContainer[step]->Draw();
}
