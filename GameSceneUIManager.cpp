//=============================================================================
//
// Game�V�[��UI�Ǘ����� [GameSceneUIManager.cpp]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "guageUI.h"
#include "scoreUI.h"
#include "starUI.h"
#include "comboUI.h"
#include "lineUI.h"
#include "trailUI.h"
#include "cursorUI.h"
#include "GameSceneUIManager.h"

//=============================================================================
// ����������
//=============================================================================
void InitGameSceneUI(void)
{
	InitGuageParts();
	InitScore();
	InitStar();
	InitCombo();
	InitLine();
	InitTrail();
	InitCursor();
}

//=============================================================================
// �I������
//=============================================================================
void UninitGameSceneUI(void)
{
	UninitGuageParts();
	UninitScore();
	UninitStar();
	UninitCombo();
	UninitLine();
	UninitTrail();
	UninitCursor();
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateGameSceneUI(HWND hWnd)
{
	UpdateGuageParts();
	UpdateScore();
	UpdateStar();
	UpdateCombo();
	UpdateLine();
	UpdateTrail();
	UpdateCursor(hWnd);

#ifdef _DEBUG
	// �f�o�b�O�p�R�}���h
	if (GetKeyboardTrigger(DIK_1))
	{
		ChangeGuage(-10);
	}
	if (GetKeyboardTrigger(DIK_2))
	{
		ChangeGuage(10);
	}
	if (GetKeyboardTrigger(DIK_3))
	{
		ChangeCombo(1);
	}
	if (GetKeyboardTrigger(DIK_4))
	{
		ChangeScore(1000);
	}
#endif

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawGameSceneUI(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, true);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	DrawGuageParts();
	DrawScore();
	DrawStar();
	DrawLine();
	DrawCombo();
	DrawTrail();

	DrawCursor();
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, false);
}

