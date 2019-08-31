//=====================================
//
//�{�X�o���b�g�K�C�h����[BossBulletGuide.cpp]
//Author:GP12A332 21 ���ԗY��
//
//=====================================
#include "BossBulletGuide.h"
#include "Framework\Easing.h"

/**************************************
�O���[�o���ϐ�
***************************************/

/**************************************
�R���X�g���N�^
***************************************/
BossBulletGuide::BossBulletGuide() :
	Polygon2D(50.0f, 50.0f),
	cntFrame(0),
	Duration(60),
	FadeDuration(10),
	currentState(State::Idle)
{
	LoadTexture("data/TEXTURE/UI/Boss/bulletGuide.png");
}

/**************************************
�X�V����
***************************************/
void BossBulletGuide::Update()
{
	if (cntFrame > Duration)
		return;

	cntFrame++;

	if (cntFrame == Duration - FadeDuration)
		currentState = State::Fadeout;
		
	if (currentState == State::Fadein)
	{
		float t = 1.0f *  cntFrame / FadeDuration;
		float alpha = Easing::EaseValue(t, 0.0f,1.0f, EaseType::Linear);
		SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, alpha));
	}
	else if (currentState == State::Fadeout)
	{
		float t = 1.0f - (float)(Duration - cntFrame) / FadeDuration;
		float alpha = Easing::EaseValue(t, 1.0f, 0.0f, EaseType::Linear);
		SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, alpha));
	}
}

/**************************************
�Z�b�g����
***************************************/
void BossBulletGuide::Set(const D3DXVECTOR3 & pos, bool isFadein)
{
	transform.pos = pos;
	cntFrame = 0;

	currentState = isFadein ? State::Fadein : State::Fadeout;
}

/**************************************
�A�N�e�B�u����
***************************************/
bool BossBulletGuide::IsActive()
{
	return cntFrame <= Duration;
}
