//=============================================================================
//
// �ړ�������ʏ��� [trail.cpp]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "trailUI.h"
#include "UIdrawer.h"
#include "starUI.h"
#include "debugWindow.h"
#include "PlayerController.h"
#include "player.h"
#include <vector>

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TRAILPARTS_MAX	(6)
#define SIZE_TRAIL		(D3DXVECTOR3(100.0f,100.0f,0.0f))
#define POSITION_TRAIL	(D3DXVECTOR3(SCREEN_WIDTH/10*9,SCREEN_HEIGHT/10*5,0.0f))

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
OBJECT	trail[TRAILPARTS_MAX];
int		historyMax;

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

		trail[i].position	= POSITION_TRAIL;
		trail[i].size		= SIZE_TRAIL;
		trail[i].rotation	= D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		SetColorObject(&trail[i], SET_COLOR_NOT_COLORED);
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
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawTrail(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �v���C���[����󂯎�����f�[�^������
	std::vector <int> drawHistory;
	GetPlayerMoveHistory(&drawHistory);

	// ��ɔw�i��`��
	DrawObject(pDevice, trail[TRAIL_BG]);
	SetVertexObject(&trail[TRAIL_BG]);

	// �v�f���v�Z
	historyMax = drawHistory.size();

	for (int i = 0; i < historyMax; i++)
	{
		DrawObject(pDevice, trail[drawHistory[i]]);
		SetVertexObject(&trail[drawHistory[i]]);
	}
}
