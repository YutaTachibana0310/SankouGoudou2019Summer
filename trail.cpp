//=============================================================================
//
// �ړ�������ʏ��� [trail.cpp]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "trail.h"
#include "UIdrawer.h"
#include "star.h"
#include "debugWindow.h"
#include "PlayerController.h"
#include "player.h"
#include "Bomb.h"


//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TRAILPARTS_MAX			(6)
#define SIZE_X_TRAIL			(100.0f)
#define SIZE_Y_TRAIL			(100.0f)
#define POSITION_TRAIL (D3DXVECTOR3(SCREEN_WIDTH/10*9,SCREEN_HEIGHT/10*5,0.0f))

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
OBJECT	trail[TRAILPARTS_MAX];
int		trailHistoryCW[MAX_LENGTH];
int		trailHistoryCCW[MAX_LENGTH];
int		historyCount = 0;
int		deleteCount = 0;
int		endArray = MAX_LENGTH - 1;

//*****************************************************************************
// �v���g�^�C�v�錾
//******************************************************************************
bool CanDrawTrailLine(int startStar,int endStar);

//=============================================================================
// ����������
//=============================================================================
HRESULT InitTrail(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �e�N�X�`���ǂݍ���
	LoadTexture(pDevice, ADRESS_TEXTURE_TRAIL_BG, &trail[TRAIL_BG]);
	LoadTexture(pDevice, ADRESS_TEXTURE_TRAIL_LINE_TOP_TO_LOWERLEFT, &trail[TRAIL_LINE_TOP_TO_LOWERLEFT]);
	LoadTexture(pDevice, ADRESS_TEXTURE_TRAIL_LINE_TOP_TO_LOWERRIGHT, &trail[TRAIL_LINE_TOP_TO_LOWERRIGHT]);
	LoadTexture(pDevice, ADRESS_TEXTURE_TRAIL_LINE_LOWERLELEFT_TO_MIDDLERIGHT, &trail[TRAIL_LINE_LOWERLEFT_TO_MIDDLERIGHT]);
	LoadTexture(pDevice, ADRESS_TEXTURE_TRAIL_LINE_LOWERRIGHT_TO_MIDDLELEFT, &trail[TRAIL_LINE_LOWERRIGHT_TO_MIDDLELEFT]);
	LoadTexture(pDevice, ADRESS_TEXTURE_TRAIL_LINE_MIDDLELEFT_TO_MIDDLERIGHT, &trail[TRAIL_LINE_MIDDLELEFT_TO_MIDDLERIGHT]);

	for (int i = 0; i < TRAILPARTS_MAX; i++)
	{
		InitialTexture(&trail[i]);
		MakeVertexObject(&trail[i]);

		trail[i].position = POSITION_TRAIL;
		trail[i].size = D3DXVECTOR3(SIZE_X_TRAIL, SIZE_Y_TRAIL, 0.0f);
		trail[i].rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		SetColorObject(&trail[i], SET_COLOR_NOT_COLORED);
	}

	// �z���v�f�Ɗ֌W�Ȃ��l�ŏ�����	
	for (int i = 0; i < MAX_LENGTH; i++)
	{
		trailHistoryCW[i] = { 8 };
		trailHistoryCCW[i] = { 8 };
	}

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitTrail(void)
{
	for (int i = 0; i < TRAILPARTS_MAX; i++)
	{
		ReleaseTexture(&trail[i]);
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateTrail(void)
{
	if (SetBomb() == true)
	{
		for (int i = 0; i < MAX_LENGTH; i++) 
		{
			trailHistoryCW[i] = { INITIAL_ARRAY_NUMBER };
			trailHistoryCCW[i] = { INITIAL_ARRAY_NUMBER };
		}
	}

	GetMove_StackCW(trailHistoryCW);
	GetMove_StackCCW(trailHistoryCCW);
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawTrail(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ��ɔw�i��`��
	DrawObject(pDevice, trail[TRAIL_BG]);
	SetVertexObject(&trail[TRAIL_BG]);

	// ���ꂼ��true�������烉�C����`��
	if (CanDrawTrailLine(TOP,LOWER_LEFT) == true)
	{
		DrawObject(pDevice, trail[TRAIL_LINE_TOP_TO_LOWERLEFT]);
		SetVertexObject(&trail[TRAIL_LINE_TOP_TO_LOWERLEFT]);
	}
	if (CanDrawTrailLine(TOP, LOWER_RIGHT) == true)
	{
		DrawObject(pDevice, trail[TRAIL_LINE_TOP_TO_LOWERRIGHT]);
		SetVertexObject(&trail[TRAIL_LINE_TOP_TO_LOWERRIGHT]);
	}
	if (CanDrawTrailLine(LOWER_LEFT, MIDDLE_RIGHT) == true)
	{
		DrawObject(pDevice, trail[TRAIL_LINE_LOWERLEFT_TO_MIDDLERIGHT]);
		SetVertexObject(&trail[TRAIL_LINE_LOWERLEFT_TO_MIDDLERIGHT]);
	}
	if (CanDrawTrailLine(LOWER_RIGHT, MIDDLE_LEFT) == true)
	{
		DrawObject(pDevice, trail[TRAIL_LINE_LOWERRIGHT_TO_MIDDLELEFT]);
		SetVertexObject(&trail[TRAIL_LINE_LOWERRIGHT_TO_MIDDLELEFT]);
	}
	if (CanDrawTrailLine(MIDDLE_LEFT, MIDDLE_RIGHT) == true)
	{
		DrawObject(pDevice, trail[TRAIL_LINE_MIDDLELEFT_TO_MIDDLERIGHT]);
		SetVertexObject(&trail[TRAIL_LINE_MIDDLELEFT_TO_MIDDLERIGHT]);
	}
}

//=============================================================================
// �`��\���菈�� (�\��������true��Ԃ�)
//=============================================================================
bool CanDrawTrailLine(int startStar, int endStar)
{
	bool canDraw;
	int	 searchFailedCount = 0;
	int	 searchSuccessCount = 0;

	for (int i = 0; i < MAX_LENGTH; i++)
	{
		// �����Ƃ����������������狳���Ă�������(>_<)

		// �z��̒��ŘA�����Ă���or�z��̍Ō�ƍŏ��ŘA�����Ă�����`�� (�S�Ă̑g�ݍ��킹�Ń`�F�b�N)
		if ((trailHistoryCW[i] == startStar && trailHistoryCW[i + 1] == endStar)
			|| (trailHistoryCW[i] == endStar && trailHistoryCW[i + 1] == startStar)
			|| (trailHistoryCCW[i] == startStar && trailHistoryCCW[i + 1] == endStar)
			|| (trailHistoryCCW[i] == endStar && trailHistoryCCW[i + 1] == startStar)
			|| (trailHistoryCW[0] == startStar && trailHistoryCW[endArray] == endStar)
			|| (trailHistoryCW[0] == endStar && trailHistoryCW[endArray] == startStar)
			|| (trailHistoryCCW[0] == startStar && trailHistoryCCW[endArray] == endStar)
			|| (trailHistoryCCW[0] == endStar && trailHistoryCCW[endArray] == startStar))
		{
			canDraw = true;
			searchSuccessCount++;
		}
		else
		{
			searchFailedCount++;
		}

		if (searchFailedCount >= MAX_LENGTH)
		{
			canDraw = false;
			searchFailedCount = 0;
		}

		if (searchSuccessCount + searchFailedCount >= MAX_LENGTH)
		{
			searchSuccessCount = 0;
			searchFailedCount = 0;
		}
	}
	return canDraw;
}
