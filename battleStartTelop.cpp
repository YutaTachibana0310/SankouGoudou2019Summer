//=============================================================================
//
// �o�g���X�^�[�g�e���b�v���� [battleStartTelop.cpp]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "telopBG.h"
#include "Framework/Easing.h"
#include "battleStartTelop.h"
#include "UIdrawer.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define SIZE_BATTLE_START_TELOP				(D3DXVECTOR3(SCREEN_WIDTH/4,50.0f,0.0f))
#define INIT_POSITION_BATTLE_START_TELOP	(D3DXVECTOR3(SCREEN_WIDTH*1.5,SCREEN_HEIGHT/10*8,0.0f))
#define ANIMATION_MAX (5)

static const float EasingStartPositionX[ANIMATION_MAX] = {
	SCREEN_WIDTH*1.5,
	SCREEN_WIDTH*1.5,
	SCREEN_CENTER_X,
	SCREEN_CENTER_X,
	-SCREEN_WIDTH * 1.5
};

static const float EasingEndPositionX[ANIMATION_MAX] = {
	SCREEN_WIDTH*1.5,
	SCREEN_CENTER_X,
	SCREEN_CENTER_X,
	-SCREEN_WIDTH * 1.5,
	-SCREEN_WIDTH * 1.5
};

static const EasingType AnimationType[ANIMATION_MAX] = {
	OutExponential,
	OutExponential,
	InOutCubic,
	InExponential,
	InExponential
};

static const float AnimationDuration[ANIMATION_MAX] = {
	10,
	120,
	100,
	120,
	10
};

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
OBJECT	battleStartTelop;
Easing<float> eBattleStartTelop;
bool isBattleStartTelopActivated = false;
static int currentAnimation = 0;

//=============================================================================
// ����������
//=============================================================================
HRESULT InitBattleStartTelop(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	LoadTexture(pDevice, ADRESS_TEXTURE_BATTLE_START_TELOP, &battleStartTelop);
	InitialTexture(&battleStartTelop);
	MakeVertexObject(&battleStartTelop);

	battleStartTelop.position = INIT_POSITION_BATTLE_START_TELOP;
	battleStartTelop.size = SIZE_BATTLE_START_TELOP;
	battleStartTelop.rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	SetColorObject(&battleStartTelop, SET_COLOR_NOT_COLORED);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitBattleStartTelop(void)
{
	ReleaseTexture(&battleStartTelop);
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateBattleStartTelop()
{	
	if (isBattleStartTelopActivated)
	{
		if (currentAnimation == WAIT_BG_OPEN && GetTelopBGOpenActive() == false)
		{
			AvctivateTelopBGOpen();
		}
		if (currentAnimation == WAIT_BG_CLOSE && GetTelopBGCloseActive() == false)
		{
			AvctivateTelopBGClose();
		}

		battleStartTelop.countFrame++;

		battleStartTelop.position.x = eBattleStartTelop.GetEasingValue(GetCountObject(
			&battleStartTelop, AnimationDuration[currentAnimation]),
			&EasingStartPositionX[currentAnimation],
			&EasingEndPositionX[currentAnimation],
			AnimationType[currentAnimation]);

		if (battleStartTelop.countFrame == AnimationDuration[currentAnimation])
		{
			battleStartTelop.countFrame = 0;
			currentAnimation++;
		}
		if (currentAnimation == ANIMATION_MAX)
		{
			battleStartTelop.countFrame = 0;
			currentAnimation = 0;
			battleStartTelop.position = INIT_POSITION_BATTLE_START_TELOP;
			isBattleStartTelopActivated = false;
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawBattleStartTelop(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	DrawObject(pDevice, battleStartTelop);
	SetVertexObject(&battleStartTelop);
}

//=============================================================================
// �o�g���X�^�[�g�e���b�v�Z�b�g����
//=============================================================================
void SetBattleStartTelop(void)
{
	isBattleStartTelopActivated = true;
}
