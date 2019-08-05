//=============================================================================
//
// �ړ�������ʏ��� [trail.cpp]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "UIdrawer.h"
#include "starUI.h"
#include "debugWindow.h"
#include "PlayerController.h"
#include "player.h"
#include <vector>
#include "trailUI.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define SIZE_TRAIL		(D3DXVECTOR3(100.0f,100.0f,0.0f))
#define POSITION_TRAIL	(D3DXVECTOR3(SCREEN_WIDTH/10*9,SCREEN_HEIGHT/10*5,0.0f))

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
int		historyMax;

//=============================================================================
// ����������
//=============================================================================
void Trail::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int i = 0; i < TRAILPARTS_MAX; i++)
	{
		// �e�N�X�`���ǂݍ���
		trail[i]->LoadTexture(pDevice, texPath[i]);

		trail[i]->InitialTexture();
		trail[i]->MakeVertexObject();

		trail[i]->position = POSITION_TRAIL;
		trail[i]->size = SIZE_TRAIL;
		trail[i]->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		trail[i]->SetColorObject(SET_COLOR_NOT_COLORED);
	}
}

//=============================================================================
// �I������
//=============================================================================
void Trail::Uninit(void)
{
	for (int i = 0; i < TRAILPARTS_MAX; i++)
	{
		trail[i]->ReleaseTexture();
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void Trail::Update(void)
{
}

//=============================================================================
// �`�揈��
//=============================================================================
void Trail::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �v���C���[����󂯎�����f�[�^������
	std::vector <int> drawHistory;
	GetPlayerMoveHistory(&drawHistory);

	// ��ɔw�i��`��
	trail[TRAIL_BG]->DrawObject(pDevice);
	trail[TRAIL_BG]->SetVertexObject();

	// �v�f���v�Z
	historyMax = drawHistory.size();

	for (int i = 0; i < historyMax; i++)
	{
		trail[drawHistory[i]]->DrawObject(pDevice);
		trail[drawHistory[i]]->SetVertexObject();
	}
}
