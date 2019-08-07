//=============================================================================
//
// Title�V�[��UI�Ǘ����� [TitleSceneUIManager.cpp]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "titleBGUI.h"
#include "titleLogoUI.h"
#include "startButtonUI.h"
#include "cursorUI.h"
#include "soundUI.h"
#include "TitleSceneUIManager.h"

//=============================================================================
// ����������
//=============================================================================
void InitTitleSceneUI(void)
{
	InitTitleBG();
	InitCursor();
	InitTitleLogo();
	InitStartButton();
	InitSoundUI();
}

//=============================================================================
// �I������
//=============================================================================
void UninitTitleSceneUI(void)
{
	UninitTitleBG();
	UninitCursor();
	UninitTitleLogo();
	UninitStartButton();
	UninitSoundUI();
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateTitleSceneUI(HWND hWnd)
{
	UpdateTitleBG();
	UpdateCursor(hWnd);
	UpdateTitleLogo();
	UpdateStartButton();
	UpdateSoundUI();
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawTitleSceneUI(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, true);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	DrawTitleBG();
	DrawTitleLogo();
	DrawStartButton();
	DrawSoundUI();

	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, false);
}

