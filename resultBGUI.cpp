//=============================================================================
//
// ���U���g�w�i��ʏ��� [resultBGUI.cpp]
// Author : �n糗Ǒ��i�����͂ܕύX�j
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "resultBGUI.h"
#include "UIdrawer.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define SIZE_RESULTBG		(D3DXVECTOR3(SCREEN_WIDTH/2,SCREEN_HEIGHT/2,0.0f))
#define POSITION_RESULTBG	(D3DXVECTOR3(SCREEN_WIDTH/2,SCREEN_HEIGHT/2,0.0f))

//*****************************************************************************
// �R���X�g���N�^
//*****************************************************************************
ResultBG::ResultBG()
{
	resultBG = new Object();

	resultBG->LoadTexture("data/TEXTURE/UI/Result/�u���b�N.jpg");
	resultBG->MakeVertex();

	resultBG->position = POSITION_RESULTBG;
	resultBG->size = SIZE_RESULTBG;
	resultBG->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	resultBG->SetColorObject(SET_COLOR_NOT_COLORED);
}

//*****************************************************************************
// �f�X�g���N�^
//*****************************************************************************
ResultBG::~ResultBG()
{
	delete resultBG;
	resultBG = NULL;
}

//=============================================================================
// �X�V����
//=============================================================================
void ResultBG::Update(void)
{
}

//=============================================================================
// �`�揈��
//=============================================================================
void ResultBG::Draw(void)
{
	resultBG->Draw();
	resultBG->SetVertex();
}
