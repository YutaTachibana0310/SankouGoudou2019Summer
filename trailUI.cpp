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
#define POSITION_TRAIL	(D3DXVECTOR3(SCREEN_WIDTH/10*9,SCREEN_HEIGHT/10*3,0.0f))

//*****************************************************************************
// �R���X�g���N�^
//*****************************************************************************
Trail::Trail()
{
	for (int i = 0; i < TRAILPARTS_MAX; i++)
	{
		trail[i] = new Object();

		// �e�N�X�`���ǂݍ���
		trail[i]->LoadTexture(texPath[i]);
		trail[i]->MakeVertex();

		trail[i]->position = POSITION_TRAIL;
		trail[i]->size = SIZE_TRAIL;
		trail[i]->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		trail[i]->SetColorObject(SET_COLOR_NOT_COLORED);
	}
}

//*****************************************************************************
// �f�X�g���N�^
//*****************************************************************************
Trail::~Trail()
{
	for (int i = 0; i < TRAILPARTS_MAX; i++)
	{
		delete trail[i];
		trail[i] = NULL;
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
	// �v���C���[����󂯎�����f�[�^������
	std::vector <int> drawHistory;
	GetPlayerMoveHistory(&drawHistory);

	// ��ɔw�i��`��
	trail[TRAIL_BG]->Draw();
	trail[TRAIL_BG]->SetVertex();

	// �v�f���v�Z
	historyMax = drawHistory.size();

	for (int i = 0; i < historyMax; i++)
	{
		trail[drawHistory[i]]->Draw();
		trail[drawHistory[i]]->SetVertex();
	}
}
