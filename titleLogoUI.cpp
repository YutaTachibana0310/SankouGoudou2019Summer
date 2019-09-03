//=============================================================================
//
// �^�C�g�����S��ʏ��� [titleLogoUI.cpp]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "titleLogoUI.h"
#include "UIdrawer.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define SIZE_TITLELOGO		(D3DXVECTOR3(SCREEN_WIDTH/4,SCREEN_HEIGHT/4,0.0f))
#define POSITION_TITLELOGO	(D3DXVECTOR3(SCREEN_WIDTH/2,SCREEN_HEIGHT/3,0.0f))

//*****************************************************************************
// �R���X�g���N�^
//*****************************************************************************
TitleLogo::TitleLogo()
{
	titleLogo = new Object();

	titleLogo->LoadTexture("data/TEXTURE/UI/�`�[�����S.png");
	titleLogo->MakeVertex();

	titleLogo->position = POSITION_TITLELOGO;
	titleLogo->size = SIZE_TITLELOGO;
	titleLogo->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	titleLogo->SetColorObject(SET_COLOR_NOT_COLORED);
}

//*****************************************************************************
// �f�X�g���N�^
//*****************************************************************************
TitleLogo::~TitleLogo()
{
	delete titleLogo;
	titleLogo = NULL;
}

//=============================================================================
// �X�V����
//=============================================================================
void TitleLogo::Update(void)
{
}

//=============================================================================
// �`�揈��
//=============================================================================
void TitleLogo::Draw(void)
{
	titleLogo->Draw();
	titleLogo->SetVertex();
}
