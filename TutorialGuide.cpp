//=====================================
//
//�`���[�g���A���K�C�h����[TutorialGuide.cpp]
//Author:GP12A332 21 ���ԗY��
//
//=====================================
#include "TutorialGuide.h"
#include "Framework\ResourceManager.h"

/**************************************
�O���[�o���ϐ�
***************************************/
const int TutorialGuide::FadeDuration = 30;
const int TutorialGuide::LifeFrame = 300;

/**************************************
�R���X�g���N�^
***************************************/
TutorialGuide::TutorialGuide() :
	cntFrame(LifeFrame)
{
	//�|���S���T�C�Y�ݒ�
	const float AspectRatio = 3.75f;
	const float Height = 65.0f;
	const float Width = Height * AspectRatio;
	SetSize(Width, Height);

	//�e�N�X�`����
	const char* TexturePath[TutorialStep::Max] = {
		"data/TEXTURE/Tutorial/tutorialstart.png",
		"data/TEXTURE/Tutorial/playermove.png",
		"data/TEXTURE/Tutorial/movebutton.png",
		"data/TEXTURE/Tutorial/comboreset.png",
		"data/TEXTURE/Tutorial/bombstock.png",
		"data/TEXTURE/Tutorial/firebomber.png",
		"data/TEXTURE/Tutorial/tutorialend.png"
	};

	//�e�N�X�`���ǂݍ���
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	textureContainer.resize(TutorialStep::Max, NULL);
	for (int i = 0; i < TutorialStep::Max; i++)
	{
		D3DXCreateTextureFromFile(pDevice, (LPCSTR)TexturePath[i], &textureContainer[i]);
	}
}

/**************************************
�X�V����
***************************************/
void TutorialGuide::Update()
{
	if (cntFrame > LifeFrame)
		return;

	cntFrame++;

	if (cntFrame <= FadeDuration)
	{
		float t = 1.0f * cntFrame / FadeDuration;
		SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, t));
	}
	else if (cntFrame >= LifeFrame - FadeDuration)
	{
		float t = 1.0f * (LifeFrame - cntFrame) / FadeDuration;
		SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, t));
	}
}

/**************************************
�`�揈��
***************************************/
void TutorialGuide::Draw()
{
	if (cntFrame > LifeFrame)
		return;

	Polygon2D::Draw();
}

/**************************************
�Z�b�g����
***************************************/
bool TutorialGuide::Set(int step)
{
	if (step >= TutorialStep::Max)
		return false;

	SetTexture(textureContainer[step]);
	cntFrame = 0;

	return true;
}
