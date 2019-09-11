//=====================================
//
//�`���[�g���A���R���g���[������[TutorialController.cpp]
//Author:GP12A332 21 ���ԗY��
//
//=====================================
#include "TutorialController.h"
#include "TutorialGuide.h"
#include "TutorialTitle.h"
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
	isFinishTitle(false),
	guide(new TutorialGuide()),
	skip(new Polygon2D()),
	title(new TutorialTitle())
{
	//���W����
	const D3DXVECTOR3 Position = D3DXVECTOR3(300.0f, 700.0f, 0.0f);
	guide->transform.pos = Position;
	guide->Set(step);

	//�X�L�b�v�K�C�h�ݒ�
	skip->LoadTexture("data/TEXTURE/Tutorial/skip.png");
	skip->SetSize(240.0f, 30.0f);
	skip->transform.pos = D3DXVECTOR3(SCREEN_WIDTH - 240.0f, SCREEN_HEIGHT - 30.0f, 0.0f);

	title->transform.pos = D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_CENTER_Y, 0.0f);
}

/**************************************
�f�X�g���N�^
***************************************/
TutorialController::~TutorialController()
{
	SAFE_DELETE(guide);
	SAFE_DELETE(skip);
}

/**************************************
�X�V����
***************************************/
void TutorialController::Update()
{
	if (isFinishTitle)
	{
		cntFrame = WrapAround(0, GuideDuration, cntFrame + 1);

		if (cntFrame == 0)
		{
			step++;
			bool isTutorialEnd = !guide->Set(step);
			if (isTutorialEnd)
				SceneChangeFlag(true, Scene::SceneGame);
		}

		guide->Update();
	}
	else
	{
		cntFrame++;

		title->Update();

		const int TitleDuration = TutorialTitle::FadeOutDuration;
		if (cntFrame == TitleDuration)
		{
			cntFrame = 0;
			isFinishTitle = true;
		}
	}
}

/**************************************
�`�揈��
***************************************/
void TutorialController::Draw()
{
	if (isFinishTitle)
		guide->Draw();
	else
		title->Draw();

	skip->Draw();
}
