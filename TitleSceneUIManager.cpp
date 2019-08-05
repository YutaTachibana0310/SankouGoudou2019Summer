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
#include "TitleSceneUIManager.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
//#define TITLE_SCENE_UI_MAX (3)

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
//TitleSceneUI *titleSceneUI[TITLE_SCENE_UI_MAX];

//=============================================================================
// ����������
//=============================================================================
void TitleSceneUI::Init(void)
{
	startButton->Init();
	titleBG->Init();
	titleLogo->Init();
}

//=============================================================================
// �I������
//=============================================================================
void TitleSceneUI::Uninit(void)
{
	startButton->Uninit();
	titleBG->Uninit();
	titleLogo->Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void TitleSceneUI::Update(HWND hWnd)
{
	startButton->Update(hWnd);
	titleBG->Update();
	titleLogo->Update();
}

//=============================================================================
// �`�揈��
//=============================================================================
void TitleSceneUI::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, true);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	startButton->Draw();
	titleBG->Draw();
	titleLogo->Draw();

	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, false);
}

