//=============================================================================
//
// UI�Ǘ����� [UIManager.cpp]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "guage.h"
#include "score.h"
#include "star.h"
#include "combo.h"
#include "line.h"
#include "trail.h"

//=============================================================================
// ����������
//=============================================================================
void InitUI(void)
{
	InitGuageParts();
	InitScore();
	InitStar();
	InitCombo();
	InitLine();
	InitTrail();
}

//=============================================================================
// �I������
//=============================================================================
void UninitUI(void)
{
	UninitGuageParts();
	UninitScore();
	UninitStar();
	UninitCombo();
	UninitLine();
	UninitTrail();
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateUI(HWND hWnd)
{
	UpdateGuageParts();
	UpdateScore();
	UpdateStar(hWnd);
	UpdateCombo();
	UpdateLine();
	UpdateTrail();

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
void DrawUI(void)
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
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, false);
}

