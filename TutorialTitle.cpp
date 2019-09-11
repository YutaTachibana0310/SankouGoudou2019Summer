//=====================================
//
//TutorialTitle.cpp
//�@�\:
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "TutorialTitle.h"
#include "Framework\Easing.h"

/**************************************
�O���[�o���ϐ�
***************************************/
const int TutorialTitle::FadeInDuration = 30;
const int TutorialTitle::ViewDuration = 60 + FadeInDuration;
const int TutorialTitle::MoveDuration = 120 + ViewDuration;
const int TutorialTitle::FadeOutDuration = 30 + MoveDuration;

/**************************************
�R���X�g���N�^
***************************************/
TutorialTitle::TutorialTitle() :
	cntFrame(0)
{
	//�e�N�X�`���ǂݍ���
	LoadTexture("data/TEXTURE/Tutorial/tutorialstart.png");

	//�T�C�Y�ݒ�
	const float AspectRatio = 3.75f;
	const float Height = 65.0f;
	const float Width = Height * AspectRatio;
	SetSize(Width, Height);
}

/**************************************
�X�V����
***************************************/
void TutorialTitle::Update()
{
	cntFrame++;

	if (cntFrame <= FadeInDuration)
	{
		float t = 1.0f * cntFrame / FadeInDuration;
		float alpha = Easing::EaseValue(t, 0.0f, 1.0f, EaseType::OutCubic);
		SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, alpha));
	}
	else if (cntFrame <= MoveDuration && cntFrame > ViewDuration)
	{
		const D3DXVECTOR3 StartPos = D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_CENTER_Y, 0.0f);
		const D3DXVECTOR3 EndPos = D3DXVECTOR3(300.0f, 700.0f, 0.0f);
		
		float t = 1.0f * (cntFrame - ViewDuration) / (MoveDuration - ViewDuration);
		transform.pos = Easing::EaseValue(t, StartPos, EndPos, EaseType::InOutCubic);
	}
	else if(cntFrame > MoveDuration)
	{
		float t = 1.0f * (cntFrame - MoveDuration) / (FadeOutDuration - MoveDuration);
		float alpha = Easing::EaseValue(t, 1.0f, 0.0f, EaseType::OutCubic);
		SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, alpha));
	}
}
