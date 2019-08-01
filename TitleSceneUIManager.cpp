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
#define TITLE_SCENE_UI_MAX (3)

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
TitleSceneUI *titleSceneUI[TITLE_SCENE_UI_MAX];

//=============================================================================
// ����������
//=============================================================================
void TitleSceneUI::Init(void)
{
	//�C���X�^���X�̐���
	TitleSceneUI *titleSceneUI[] = {
		new TitleBG(), new TitleLogo(), new StartButton(),
	};

	for (int i = 0; i < TITLE_SCENE_UI_MAX; i++)
	{
		titleSceneUI[i]->Init();
	}
}

//=============================================================================
// �I������
//=============================================================================
void TitleSceneUI::Uninit(void)
{
	for (int i = 0; i < TITLE_SCENE_UI_MAX; i++)
	{
		titleSceneUI[i]->Uninit();
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void TitleSceneUI::Update(HWND hWnd)
{
	for (int i = 0; i < TITLE_SCENE_UI_MAX; i++)
	{
		titleSceneUI[i]->Update(hWnd);
	}
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

	for (int i = 0; i < TITLE_SCENE_UI_MAX; i++)
	{
		titleSceneUI[i]->Draw();
	}

	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, false);
}

