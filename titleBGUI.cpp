//=============================================================================
//
// �^�C�g���w�i��ʏ��� [titleBGUI.cpp]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "titleBGUI.h"
#include "UIdrawer.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define SIZE_TITLEBG		(D3DXVECTOR3(SCREEN_WIDTH/2,SCREEN_HEIGHT/2,0.0f))
#define POSITION_TITLEBG	(D3DXVECTOR3(SCREEN_WIDTH/2,SCREEN_HEIGHT/2,0.0f))

//*****************************************************************************
// �R���X�g���N�^
//*****************************************************************************
TitleBG::TitleBG()
{
	titleBG = new Object();

	titleBG->LoadTexture("data/TEXTURE/UI/titleBG.jpg");
	titleBG->MakeVertex();

	titleBG->position = POSITION_TITLEBG;
	titleBG->size = SIZE_TITLEBG;
	titleBG->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	titleBG->SetColorObject(SET_COLOR_NOT_COLORED);
}

//*****************************************************************************
// �f�X�g���N�^
//*****************************************************************************
TitleBG::~TitleBG()
{
	SAFE_DELETE(titleBG);
}

//=============================================================================
// �X�V����
//=============================================================================
void TitleBG:: Update(void)
{
}

//=============================================================================
// �`�揈��
//=============================================================================
void TitleBG::Draw(void)
{
	titleBG->Draw();
	titleBG->SetVertex();
}
