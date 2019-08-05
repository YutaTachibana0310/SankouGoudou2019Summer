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
void OpenTelopBG(void);
void CloseTelopBG(void);
void SetEasingValueTelopBGOpen(void);
void SetEasingValueTelopBGClose(void);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
OBJECT	telopBG;
Easing eTelopBG;
static float	percentage;

bool telopBGOpenActivated = false;
bool telopBGCloseActivated = false;

//=============================================================================
// ����������
//=============================================================================
HRESULT InitTelopBG(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	LoadTexture(pDevice, ADRESS_TEXTURE_TELOP_BG, &telopBG);
	InitialTexture(&telopBG);
	MakeVertexObject(&telopBG);

	telopBG.position = POSITION_TELOP_BG;
	telopBG.size	 = SIZE_TELOP_BG;
	telopBG.rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	SetColorObject(&telopBG, SET_COLOR_NOT_COLORED);

	percentage = INITIALVALUE_BG_PERCENTAGE;

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitTelopBG(void)
{
	ReleaseTexture(&telopBG);
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateTelopBG(void)
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
void DrawTelopBG(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	DrawObject(pDevice, telopBG);
	SetVertexTelopBG(&telopBG, percentage);
}

//=============================================================================
// �w�i���J������
//=============================================================================
void OpenTelopBG(void)
{
	SetEasingValueTelopBGOpen();
	percentage = eTelopBG.EaseValue(GetCountObject(&telopBG, DURATION_OPEN_CLOSE), telopBG.easingStart, telopBG.easingGoal, InOutCubic);

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
void CloseTelopBG(void)
{
	SetEasingValueTelopBGClose();
	percentage = eTelopBG.EaseValue(GetCountObject(&telopBG ,DURATION_OPEN_CLOSE), telopBG.easingStart, telopBG.easingGoal, InOutCubic);

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
void SetEasingValueTelopBGOpen(void)
{	
	telopBG.easingStart = INITIALVALUE_BG_PERCENTAGE;
	telopBG.easingGoal = 1.0f;
}

//=============================================================================
// �w�iclose�C�[�W���O�Z�b�g����
//=============================================================================
void SetEasingValueTelopBGClose(void)
{
	telopBG.easingStart = 1.0f;
	telopBG.easingGoal = INITIALVALUE_BG_PERCENTAGE;
}

//=============================================================================
// �e���b�v�w�i�J�n�A�N�e�B�x�[�g����
//=============================================================================
void AvctivateTelopBGOpen(void)
{
	telopBGOpenActivated = true;
}

//=============================================================================
// �e���b�v�w�i�I���A�N�e�B�x�[�g����
//=============================================================================
void AvctivateTelopBGClose(void)
{
	telopBGCloseActivated = true;
}

//=============================================================================
// �e���b�v�w�i�J�n�A�N�e�B�u��Ԏ擾����
//=============================================================================
bool GetTelopBGOpenActive(void)
{
	return telopBGOpenActivated;
}

//=============================================================================
// �e���b�v�w�i�I���A�N�e�B�u��Ԏ擾����
//=============================================================================
bool GetTelopBGCloseActive(void)
{
	return telopBGCloseActivated;
}