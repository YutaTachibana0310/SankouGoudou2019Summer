//=============================================================================
//
// �e���b�v�w�i���� [telopBG.cpp]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "telopBG.h"
#include "Framework/Easing.h"
#include "debugWindow.h"
#include "battleStartTelop.h"
#include "UIdrawer.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define SIZE_TELOP_BG		(D3DXVECTOR3(SCREEN_WIDTH/4,50.0f,0.0f))
#define POSITION_TELOP_BG	(D3DXVECTOR3(SCREEN_WIDTH/2,SCREEN_HEIGHT/10*8,0.0f))
#define INITIALVALUE_BG_PERCENTAGE (0.0f)
#define DURATION_OPEN_CLOSE (20.0f)

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
Object	telopBG;
Easing<float> eTelopBG;
static float	percentage;

bool telopBGOpenActivated = false;
bool telopBGCloseActivated = false;

//=============================================================================
// ����������
//=============================================================================
void TelopBG::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	object->LoadTexture(pDevice, ADRESS_TEXTURE_TELOP_BG, &telopBG);
	object->InitialTexture(&telopBG);
	object->MakeVertexObject(&telopBG);

	telopBG.position = POSITION_TELOP_BG;
	telopBG.size	 = SIZE_TELOP_BG;
	telopBG.rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	object->SetColorObject(&telopBG, SET_COLOR_NOT_COLORED);

	percentage = INITIALVALUE_BG_PERCENTAGE;
}

//=============================================================================
// �I������
//=============================================================================
void TelopBG::Uninit(void)
{
	object->ReleaseTexture(&telopBG);
}

//=============================================================================
// �X�V����
//=============================================================================
void TelopBG::Update(void)
{
	//�@���ӂ�h�~
	if (percentage < 0)
	{
		percentage = 0;
	}
	if (percentage > 1.0f)
	{
		percentage = 1.0f;
	}

	if (telopBGOpenActivated)
	{
		OpenTelopBG();
	}

	if (telopBGCloseActivated)
	{
		CloseTelopBG();
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void TelopBG::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	object->DrawObject(pDevice, &telopBG);
	object->SetVertexTelopBG(&telopBG, percentage);
}

//=============================================================================
// �w�i���J������
//=============================================================================
void TelopBG::OpenTelopBG(void)
{
	SetEasingValueTelopBGOpen();
	percentage = eTelopBG.GetEasingValue(object->GetCountObject(&telopBG, DURATION_OPEN_CLOSE), &telopBG.easingStart, &telopBG.easingGoal, InOutCubic);

	if(percentage >= telopBG.easingGoal)
	{
		telopBGOpenActivated = false;
		percentage = 1.0f;
		telopBG.countFrame = 0;
	}
}

//=============================================================================
// �w�i����鏈��
//=============================================================================
void TelopBG::CloseTelopBG(void)
{
	SetEasingValueTelopBGClose();
	percentage = eTelopBG.GetEasingValue(object->GetCountObject(&telopBG ,DURATION_OPEN_CLOSE), &telopBG.easingStart, &telopBG.easingGoal, InOutCubic);

	if(percentage <= telopBG.easingGoal)
	{
		telopBGCloseActivated = false;
		percentage = 0.0f;
		telopBG.countFrame = 0;
	}
}

//=============================================================================
// �w�iopen�C�[�W���O�Z�b�g����
//=============================================================================
void TelopBG::SetEasingValueTelopBGOpen(void)
{	
	telopBG.easingStart = INITIALVALUE_BG_PERCENTAGE;
	telopBG.easingGoal = 1.0f;
}

//=============================================================================
// �w�iclose�C�[�W���O�Z�b�g����
//=============================================================================
void TelopBG::SetEasingValueTelopBGClose(void)
{
	telopBG.easingStart = 1.0f;
	telopBG.easingGoal = INITIALVALUE_BG_PERCENTAGE;
}

//=============================================================================
// �e���b�v�w�i�J�n�A�N�e�B�x�[�g����
//=============================================================================
void TelopBG::AvctivateTelopBGOpen(void)
{
	telopBGOpenActivated = true;
}

//=============================================================================
// �e���b�v�w�i�I���A�N�e�B�x�[�g����
//=============================================================================
void TelopBG::AvctivateTelopBGClose(void)
{
	telopBGCloseActivated = true;
}

//=============================================================================
// �e���b�v�w�i�J�n�A�N�e�B�u��Ԏ擾����
//=============================================================================
bool TelopBG::GetTelopBGOpenActive(void)
{
	return telopBGOpenActivated;
}

//=============================================================================
// �e���b�v�w�i�I���A�N�e�B�u��Ԏ擾����
//=============================================================================
bool TelopBG::GetTelopBGCloseActive(void)
{
	return telopBGCloseActivated;
}