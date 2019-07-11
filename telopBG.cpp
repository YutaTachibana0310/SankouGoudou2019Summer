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
#include "UIdrawer.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define SIZE_TELOP_BG		(D3DXVECTOR3(SCREEN_WIDTH/4,50.0f,0.0f))
#define POSITION_TELOP_BG	(D3DXVECTOR3(SCREEN_WIDTH/2,SCREEN_HEIGHT/10*8,0.0f))
#define INITIALVALUE_BG_PERCENTAGE (0.0f)
#define DURATION_ZOOM_IN_OUT (30.0f)

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void GetThickTelopBG(void);
void GetThinTelopBG(void);
float GetCountTelopBG(void);
void SetEasingValueTelopBG(void);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
OBJECT	telopBG;
Easing<float> eTelopBG;
float	percentage;

bool telopBGInActivated = false;
bool telopBGOutActivated = false;

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
	telopBG.size = SIZE_TELOP_BG;
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
	if (percentage <= 0)
	{
		percentage = 0;
	}
	if (percentage >= 1.0f)
	{
		percentage = 1.0f;
	}

	if (GetKeyboardTrigger(DIK_8))
	{
		telopBG.countFrame = 0;

		percentage = 0.0f;
		telopBGInActivated = true;
	}
	if (GetKeyboardTrigger(DIK_9))
	{
		telopBG.countFrame = 0;

		percentage = 1.0f;
		telopBGOutActivated = true;
	}

	//SetEasingValueTelopBG();

	//DebugLog("telopBGInActivated:%n\n", telopBGInActivated);
	//DebugLog("telopBGOutActivated:%n\n", telopBGOutActivated);

	if (telopBGInActivated)
	{
		percentage = eTelopBG.GetEasingValue(GetCountTelopBG(), &telopBG.easingStart, &telopBG.easingGoal, OutExponential);
		GetThickTelopBG();
	}

	if (telopBGOutActivated)
	{
		percentage = eTelopBG.GetEasingValue(GetCountTelopBG(), &telopBG.easingStart, &telopBG.easingGoal, OutExponential);
		GetThinTelopBG();
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
// �w�i�𑾂����鏈��
//=============================================================================
void GetThickTelopBG(void)
{
	telopBG.easingStart = INITIALVALUE_BG_PERCENTAGE;
	telopBG.easingGoal = 1.0f;

	//percentage = eTelopBG.GetEasingValue(GetCountTelopBG(), &telopBG.easingStart, &telopBG.easingGoal, OutExponential);

	if(percentage >= telopBG.easingGoal)
	{
		percentage = 1.0f;
		telopBGInActivated = false;
	}
}

//=============================================================================
// �w�i���ׂ����鏈��
//=============================================================================
void GetThinTelopBG(void)
{
	telopBG.easingStart = 1.0f;
	telopBG.easingGoal = INITIALVALUE_BG_PERCENTAGE;

	//percentage = eTelopBG.GetEasingValue(GetCountTelopBG(), &telopBG.easingStart, &telopBG.easingGoal, OutExponential);

	if(percentage <= telopBG.easingGoal)
	{
		percentage = 0.0f;
		telopBGOutActivated = false;
	}
}

//=============================================================================
// �J�E���g�擾����
//=============================================================================
float GetCountTelopBG(void)
{
	telopBG.countFrame++;
	float t = (float)telopBG.countFrame / DURATION_ZOOM_IN_OUT;

	return t;
}

//=============================================================================
// �C�[�W���O�Z�b�g����
//=============================================================================
void SetEasingValueTelopBG(void)
{	
	if (telopBGInActivated)
	{
		telopBG.easingStart = INITIALVALUE_BG_PERCENTAGE;
		telopBG.easingGoal = 1.0f;
	}
	if (telopBGOutActivated)
	{
		telopBG.easingStart = 1.0f;
		telopBG.easingGoal = INITIALVALUE_BG_PERCENTAGE;
	}
}