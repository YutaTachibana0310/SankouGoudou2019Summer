//=============================================================================
//
// �Q�[�W��ʏ��� [guage.cpp]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "guageUI.h"
#include "UIdrawer.h"
#include "debugWindow.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	GUAGEPARTS_MAX		(4)
#define WIDTH_GUAGEFLAME	(5.0f)
#define MAX_HP				(100)
#define DECREASESPEED_GUAGE (0.0050f)
#define TEXT_GUAGE_ALPHA	(0.5f)
#define INITIALVALUE_GUAGEPERCENTAGE (1.0f)
#define SIZE_GUAGE			(D3DXVECTOR3(25.0f,250.0f,0.0f))
#define POSITION_GUAGE		(D3DXVECTOR3(SCREEN_WIDTH / 10*1.0f, SCREEN_HEIGHT / 10*7.0f, 0.0f))

//=============================================================================
// ����������
//=============================================================================
void Guage::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	damageGuage->LoadTexture(pDevice, ADRESS_TEXTURE_GUAGEBAR);
	hPGuage->LoadTexture(pDevice, ADRESS_TEXTURE_GUAGEBAR);
	guageFlame->LoadTexture(pDevice, ADRESS_TEXTURE_GUAGEFLAME);
	guageText->LoadTexture(pDevice, ADRESS_TEXTURE_GUAGETEXT);

	damageGuage->MakeVertexGuageBar(damageGuagePercentage,	WIDTH_GUAGEFLAME);
	hPGuage->MakeVertexGuageBar(trueGuagePercentage,	WIDTH_GUAGEFLAME);
	guageFlame->MakeVertexObject();
	guageText->MakeVertexObject();

	damageGuage->position = POSITION_GUAGE;
	hPGuage->position = POSITION_GUAGE;
	guageFlame->position = POSITION_GUAGE;
	guageText->position = POSITION_GUAGE;

	damageGuage->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	hPGuage->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	guageFlame->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	guageText->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	damageGuage->size = SIZE_GUAGE;
	hPGuage->size = SIZE_GUAGE;
	guageFlame->size = SIZE_GUAGE;
	guageText->size = SIZE_GUAGE;
	
	damageGuage->InitialTexture();
	hPGuage->InitialTexture();
	guageFlame->InitialTexture();
	guageText->InitialTexture();

	//�@�F�ݒ�
	damageGuage->SetColorObject(SET_COLOR_RED);
	hPGuage->SetColorObject(SET_COLOR_YELLOW);
	guageFlame->SetColorObject(SET_COLOR_NOT_COLORED);
	guageText->SetColorObject(D3DXCOLOR(0.0f, 0.0f, 0.0f, TEXT_GUAGE_ALPHA));

	damageGuagePercentage = INITIALVALUE_GUAGEPERCENTAGE;
	trueGuagePercentage   = INITIALVALUE_GUAGEPERCENTAGE;
}

//=============================================================================
// �I������
//=============================================================================
void Guage::Uninit(void)
{
	damageGuage->ReleaseTexture();
	hPGuage->ReleaseTexture();
	guageFlame->ReleaseTexture();
	guageText->ReleaseTexture();
}

//=============================================================================
// �X�V����
//=============================================================================
void Guage::Update(void)
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
void Guage::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	damageGuage->DrawObject(pDevice);
	hPGuage->DrawObject(pDevice);
	guageFlame->DrawObject(pDevice);
	guageText->DrawObject(pDevice);

	// ���_���W�̐ݒ�
	damageGuage->SetVertexGuageBar(damageGuagePercentage, WIDTH_GUAGEFLAME, DOWN_GUAGEBAR);
	hPGuage->SetVertexGuageBar(trueGuagePercentage,	WIDTH_GUAGEFLAME, DOWN_GUAGEBAR);
	guageFlame->SetVertexObject();
	guageText->SetVertexObject();
}

//=============================================================================
// HP�̕ύX
//=============================================================================
void Guage::ChangeGuage(float value)
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
