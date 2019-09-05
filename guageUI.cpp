//=============================================================================
//
// �Q�[�W��ʏ��� [guage.cpp]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "UIdrawer.h"
#include "debugWindow.h"
#include "Viewer3D.h"
#include "guageUI.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define WIDTH_GUAGEFLAME	(3.5f)
#define DECREASESPEED_GUAGE (0.0050f)
#define INITIALVALUE_GUAGEPERCENTAGE (1.0f)
#define SIZE_GUAGE			(D3DXVECTOR3(190.0f,25.0f,0.0f))
#define SIZE_GUAGE_BG		(D3DXVECTOR3(250.0f,25.0f,0.0f))

////���W�ݒ�(2D)
//#define POSITION_GUAGE	(D3DXVECTOR3(SCREEN_WIDTH / 10*7.63f, SCREEN_HEIGHT / 10*1.0f, 0.0f))
//#define POSITION_BG_GUAGE	(D3DXVECTOR3(SCREEN_WIDTH / 10*8.0f, SCREEN_HEIGHT / 10*1.0f, 0.0f))

//���W�ݒ�(3D)
#define POSITION_GUAGE		(D3DXVECTOR3(190.0f,25.0f,0.0f))
#define POSITION_BG_GUAGE	(D3DXVECTOR3(250.0f,25.0f,0.0f))

//*****************************************************************************
// �R���X�g���N�^
//*****************************************************************************
Guage::Guage()
{
	//�_���[�W�Q�[�W
	damageGuage = new GuageObject();
	damageGuage->LoadTexture("data/TEXTURE/UI/HP/guageBody.png");
	damageGuage->MakeVertex(damageGuagePercentage, WIDTH_GUAGEFLAME);
	damageGuage->position = POSITION_GUAGE/2;
	damageGuage->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	damageGuage->size = SIZE_GUAGE/2;
	damageGuage->SetColorObject(SET_COLOR_RED);

	//HP�Q�[�W
	hPGuage = new GuageObject();
	hPGuage->LoadTexture("data/TEXTURE/UI/HP/guageBody.png");
	hPGuage->MakeVertex(trueGuagePercentage, WIDTH_GUAGEFLAME);
	hPGuage->position = POSITION_GUAGE/2;
	hPGuage->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	hPGuage->size = SIZE_GUAGE/2;
	hPGuage->SetColorObject(SET_COLOR_NOT_COLORED);

	//�Q�[�W�t���[��
	frame = new Object();
	frame->LoadTexture("data/TEXTURE/UI/HP/guageFrame.png");
	frame->MakeVertex();
	frame->position = POSITION_GUAGE/2;
	frame->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	frame->size = SIZE_GUAGE/2;
	frame->SetColorObject(SET_COLOR_NOT_COLORED);

	//�Q�[�W�w�i
	bg = new Object();
	bg->LoadTexture("data/TEXTURE/UI/HP/guageBG.png");
	bg->MakeVertex();
	bg->position = POSITION_BG_GUAGE/2;
	bg->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	bg->size = SIZE_GUAGE_BG/2;
	bg->SetColorObject(SET_COLOR_NOT_COLORED);

	//�r���A�[
	viewer = new Viewer3D(SIZE_GUAGE_BG.x, SIZE_GUAGE_BG.y, D3DXVECTOR2(35.0f, 8.0f));
	viewer->SetPosition(D3DXVECTOR3(95.0f, 65.0f,0.0f));
	viewer->SetRotation(0.0f, 30.0f, 0.0f);

	//�����Q�[�W�p�[�Z���e�[�W�ݒ�
	damageGuagePercentage = INITIALVALUE_GUAGEPERCENTAGE;
	trueGuagePercentage = INITIALVALUE_GUAGEPERCENTAGE;
}

//*****************************************************************************
// �f�X�g���N�^
//*****************************************************************************
Guage::~Guage()
{
	delete damageGuage;
	damageGuage = NULL;

	delete hPGuage;
	hPGuage = NULL;

	delete frame;
	frame = NULL;

	delete bg;
	bg = NULL;

	delete viewer;
	viewer = NULL;
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

	// ���ӂ�h�~
	if (trueGuagePercentage <= 0.0f)
	{
		trueGuagePercentage = 0.0f;
	}
	if (trueGuagePercentage >= INITIALVALUE_GUAGEPERCENTAGE)
	{
		trueGuagePercentage = INITIALVALUE_GUAGEPERCENTAGE;
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

//=============================================================================
// �`�揈��
//=============================================================================
void Guage::Draw(void)
{
	viewer->Begin2D();

	bg->Draw();
	damageGuage->Draw();
	hPGuage->Draw();
	frame->Draw();

	// ���_���W�̐ݒ�
	damageGuage->SetVertex(damageGuagePercentage, WIDTH_GUAGEFLAME, damageGuage->LEFT_GUAGEBAR);
	hPGuage->SetVertex(trueGuagePercentage,	WIDTH_GUAGEFLAME, hPGuage->LEFT_GUAGEBAR);
	frame->SetVertex();
	bg->SetVertex();

	viewer->End2D();
	viewer->Draw3D();
}
