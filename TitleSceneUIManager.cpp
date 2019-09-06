//=============================================================================
//
// Title�V�[��UI�Ǘ����� [TitleSceneUIManagerManager.cpp]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "titleBGUI.h"
#include "titleLogoUI.h"
#include "startButtonUI.h"
#include "cursorUI.h"
#include "masktex.h"
#include "TitleSceneUIManager.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
//#define TITLE_SCENE_UI_MAX (3)

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
//TitleSceneUIManager *titleSceneUI[TITLE_SCENE_UI_MAX];

//*****************************************************************************
// �R���X�g���N�^
//*****************************************************************************
TitleSceneUIManager::TitleSceneUIManager()
{
	startButton = new StartButton();
	titleBG = new TitleBG();
	titleLogo = new TitleLogo();
}

//*****************************************************************************
// �f�X�g���N�^
//*****************************************************************************
TitleSceneUIManager::~TitleSceneUIManager()
{
	SAFE_DELETE(startButton);
	SAFE_DELETE(titleBG);
	SAFE_DELETE(titleLogo);
}

//=============================================================================
// ����������
//=============================================================================
void TitleSceneUIManager::Init()
{

}

//=============================================================================
// �I������
//=============================================================================
void TitleSceneUIManager::Uninit()
{

}

//=============================================================================
// �X�V����
//=============================================================================
void TitleSceneUIManager::Update(HWND hWnd)
{
	startButton->Update(hWnd);
	titleBG->Update();
	titleLogo->Update();
}

//=============================================================================
// �`�揈��
//=============================================================================
void TitleSceneUIManager::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, true);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	titleBG->Draw();
	titleLogo->Draw();
	startButton->Draw();

	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, false);
}

