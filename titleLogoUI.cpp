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
// �O���[�o���ϐ�
//*****************************************************************************
Object titleLogo;

//=============================================================================
// ����������
//=============================================================================
void TitleLogo::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	object->LoadTexture(pDevice, ADRESS_TEXTURE_TITLELOGO, &titleLogo);
	object->InitialTexture(&titleLogo);
	object->MakeVertexObject(&titleLogo);

	titleLogo.position	= POSITION_TITLELOGO;
	titleLogo.size		= SIZE_TITLELOGO;
	titleLogo.rotation	= D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	object->SetColorObject(&titleLogo, SET_COLOR_NOT_COLORED);
}

//=============================================================================
// �I������
//=============================================================================
void TitleLogo::Uninit(void)
{
	object->ReleaseTexture(&titleLogo);
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
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	object->DrawObject(pDevice, &titleLogo);
	object->SetVertexObject(&titleLogo);
}
