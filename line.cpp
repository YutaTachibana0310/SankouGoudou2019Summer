//=============================================================================
//
// �C���^�[�t�F�[�X���C����ʏ��� [line.cpp]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "line.h"
#include "UIdrawer.h"
#include "collider.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define SIZE_X_LINE			(780.0f)
#define SIZE_Y_LINE			(450.0f)
#define POSITION_LINE (D3DXVECTOR3(SCREEN_WIDTH/2,SCREEN_HEIGHT/2,0.0f))

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
OBJECT	line;

//=============================================================================
// ����������
//=============================================================================
HRESULT InitLine(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	LoadTexture(pDevice, ADRESS_TEXTURE_LINE, &line);
	InitialTexture(&line);
	MakeVertexRotateObject(&line);

	line.position = POSITION_LINE;
	line.size = D3DXVECTOR3(SIZE_X_LINE, SIZE_Y_LINE, 0.0f);
	line.rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	SetColorObject(&line, SET_COLOR_NOT_COLORED);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitLine(void)
{
	ReleaseTexture(&line);
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateLine()
{
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawLine(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	DrawObject(pDevice, line);
	SetVertexObject(&line);
}
