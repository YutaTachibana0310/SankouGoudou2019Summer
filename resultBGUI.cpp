//=============================================================================
//
// ���U���g�w�i��ʏ��� [resultBGUI.cpp]
// Author : �n糗Ǒ�
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "resultBGUI.h"
#include "UIdrawerC.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define SIZE_RESULTBG		(D3DXVECTOR3(SCREEN_WIDTH/2,SCREEN_HEIGHT/2,0.0f))
#define POSITION_RESULTBG	(D3DXVECTOR3(SCREEN_WIDTH/2,SCREEN_HEIGHT/2,0.0f))

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
OBJECT	resultBG;

//=============================================================================
// ����������
//=============================================================================
HRESULT InitResultBG(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	LoadTexture(pDevice, ADRESS_TEXTURE_RESULTBG, &resultBG);
	InitialTexture(&resultBG);
	MakeVertexObject(&resultBG);

	resultBG.position = POSITION_RESULTBG;
	resultBG.size = SIZE_RESULTBG;
	resultBG.rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	SetColorObject(&resultBG, SET_COLOR_NOT_COLORED);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitResultBG(void)
{
	ReleaseTexture(&resultBG);
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateResultBG(void)
{
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawResultBG(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, false);

	DrawObject(pDevice, resultBG);
	SetVertexObject(&resultBG);

	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, true);
}