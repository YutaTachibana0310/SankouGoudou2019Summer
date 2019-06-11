//=============================================================================
//
// �Q�[�W��ʏ��� [guage.cpp]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "guage.h"
#include "UIdrawer.h"
#include "debugWindow.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	GUAGEPARTS_MAX		(4)
#define WIDTH_GUAGEFLAME	(5.0f)
#define MAX_HP				(100)
#define DECREASESPEED_GUAGE (0.0050f)
#define SIZE_X_GUAGE		(25.0f)
#define SIZE_Y_GUAGE		(250.0f)
#define POSITION_GUAGE		(D3DXVECTOR3(SCREEN_WIDTH / 10*1.0f, SCREEN_HEIGHT / 10*7.0f, 0.0f))
#define INITIALVALUE_GUAGEPERCENTAGE (1.0f)
#define TEXT_GUAGE_ALPHA	(0.5f)

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
OBJECT	guageParts[GUAGEPARTS_MAX];
float	damageGuagePercentage;	//�_���[�W�\���Q�[�W�p�[�Z���e�[�W
float	trueGuagePercentage;	//���ۂ̃Q�[�W�p�[�Z���e�[�W

//=============================================================================
// ����������
//=============================================================================
HRESULT InitGuageParts(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	LoadTexture(pDevice, ADRESS_TEXTURE_GUAGEBAR,	&guageParts[GUAGEBAR_DAMAGE]);
	LoadTexture(pDevice, ADRESS_TEXTURE_GUAGEBAR,	&guageParts[GUAGEBAR_TRUE]);
	LoadTexture(pDevice, ADRESS_TEXTURE_GUAGEFLAME, &guageParts[GUAGEFLAME]);
	LoadTexture(pDevice, ADRESS_TEXTURE_GUAGETEXT, &guageParts[GUAGETEXT]);

	MakeVertexGuageBar(&guageParts[GUAGEBAR_DAMAGE],damageGuagePercentage,	WIDTH_GUAGEFLAME);
	MakeVertexGuageBar(&guageParts[GUAGEBAR_TRUE],	trueGuagePercentage,	WIDTH_GUAGEFLAME);
	MakeVertexObject  (&guageParts[GUAGEFLAME]);
	MakeVertexObject(&guageParts[GUAGETEXT]);

	for (int i = 0; i < GUAGEPARTS_MAX; i++)
	{
		guageParts[i].position = POSITION_GUAGE;
		guageParts[i].rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		guageParts[i].size     = D3DXVECTOR3(SIZE_X_GUAGE, SIZE_Y_GUAGE, 0.0f);

		InitialTexture(&guageParts[i]);
	}

	//�@�F�ݒ�
	SetColorObject(&guageParts[GUAGEBAR_DAMAGE], SET_COLOR_RED);
	SetColorObject(&guageParts[GUAGEBAR_TRUE],	 SET_COLOR_YELLOW);
	SetColorObject(&guageParts[GUAGEFLAME],		 SET_COLOR_NOT_COLORED);
	SetColorObject(&guageParts[GUAGETEXT], D3DXCOLOR(0.0f, 0.0f, 0.0f, TEXT_GUAGE_ALPHA));

	damageGuagePercentage = INITIALVALUE_GUAGEPERCENTAGE;
	trueGuagePercentage   = INITIALVALUE_GUAGEPERCENTAGE;

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitGuageParts(void)
{
	for (int i = 0; i < GUAGEPARTS_MAX; i++)
	{
		ReleaseTexture(&guageParts[i]);
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateGuageParts(void)
{
	//�_���[�W�\���Q�[�W�p�[�Z���e�[�W�����ۂ̃Q�[�W�p�[�Z���e�[�W�Ɠ����ɂȂ�܂Ō��Z
	if (damageGuagePercentage > trueGuagePercentage)
	{
		damageGuagePercentage -= DECREASESPEED_GUAGE;
	}
	if (damageGuagePercentage < trueGuagePercentage)
	{
		damageGuagePercentage = trueGuagePercentage;
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawGuageParts(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int i = 0; i < GUAGEPARTS_MAX; i++)
	{
		DrawObject(pDevice, guageParts[i]);
	}

	// ���_���W�̐ݒ�
	SetVertexGuageBar(&guageParts[GUAGEBAR_DAMAGE],	damageGuagePercentage,	WIDTH_GUAGEFLAME, DOWN_GUAGEBAR);
	SetVertexGuageBar(&guageParts[GUAGEBAR_TRUE],	trueGuagePercentage,	WIDTH_GUAGEFLAME, DOWN_GUAGEBAR);
	SetVertexObject(&guageParts[GUAGEFLAME]);
	//SetVertexObject(&guageParts[GUAGETEXT]);
}

//=============================================================================
// HP�̕ύX
//=============================================================================
void ChangeGuage(float value)
{
	trueGuagePercentage += (value /= MAX_HP);

	// ���ӂ�h�~
	if (trueGuagePercentage	<= 0.0f)
	{
		trueGuagePercentage = 0.0f;
	}
	if (trueGuagePercentage >= INITIALVALUE_GUAGEPERCENTAGE)
	{
		trueGuagePercentage	= INITIALVALUE_GUAGEPERCENTAGE;
	}
	if (damageGuagePercentage <= 0.0f)
	{
		damageGuagePercentage = 0.0f;
	}
	if (damageGuagePercentage >= INITIALVALUE_GUAGEPERCENTAGE)
	{
		damageGuagePercentage = INITIALVALUE_GUAGEPERCENTAGE;
	}
}
