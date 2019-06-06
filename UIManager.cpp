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

//=============================================================================
// ����������
//=============================================================================
void InitUIManager(void)
{
	InitGuageParts();
	InitScore();
	InitStar();
	InitCombo();
	InitLine();
}

//=============================================================================
// �I������
//=============================================================================
void UninitUIManager(void)
{
	UninitGuageParts();
	UninitScore();
	UninitStar();
	UninitCombo();
	UninitLine();
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateUIManager(HWND hWnd)
{
	UpdateGuageParts();
	UpdateScore();
	UpdateStar(hWnd);
	UpdateCombo();
	UpdateLine();

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
void DrawUIManager(void)
{
	DrawGuageParts();
	DrawScore();
	DrawStar();
	DrawCombo();
	DrawLine();
}

