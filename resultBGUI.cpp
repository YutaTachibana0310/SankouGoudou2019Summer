//=============================================================================
//
// ���U���g�w�i��ʏ��� [resultBGUI.cpp]
// Author : �n糗Ǒ�
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
// �O���[�o���ϐ�
//*****************************************************************************
Object	resultBG;

//=============================================================================
// ����������
//=============================================================================
void ResultBG::Init(void)
{
	//LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//object->LoadTexture(pDevice, ADRESS_TEXTURE_RESULTBG, &resultBG);
	//object->InitialTexture(&resultBG);
	//object->MakeVertexObject(&resultBG);

	//resultBG.position = POSITION_RESULTBG;
	//resultBG.size = SIZE_RESULTBG;
	//resultBG.rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//object->SetColorObject(&resultBG, SET_COLOR_NOT_COLORED);
}

//=============================================================================
// �I������
//=============================================================================
void ResultBG::Uninit(void)
{
	//object->ReleaseTexture(&resultBG);
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
	//LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//object->DrawObject(pDevice, &resultBG);
	//object->SetVertexObject(&resultBG);
}
