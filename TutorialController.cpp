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
	step(0),
	guide(new TutorialGuide())
{
	//���W����
	const D3DXVECTOR3 Position = D3DXVECTOR3(300.0f, 700.0f, 0.0f);
	guide->transform.pos = Position;
	guide->Set(step);
}

/**************************************
�f�X�g���N�^
***************************************/
TutorialController::~TutorialController()
{
	SAFE_DELETE(guide);
}

/**************************************
�X�V����
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
�`�揈��
***************************************/
void TutorialController::Draw()
{
	guide->Draw();
}
