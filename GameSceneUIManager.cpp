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
#include "battleStartTelop.h"
#include "stageClearTelop.h"
#include "telopBG.h"
#include "GameSceneUIManager.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
//#define GAME_SCENE_UI_MAX (10)

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
//GameSceneUI *gameSceneUI[GAME_SCENE_UI_MAX];

//=============================================================================
// ����������
//=============================================================================
void GameSceneUI::Init(void)
{
	line->Init();
	cursor->Init();
	combo->Init();
	guage->Init();
	score->Init();
	star->Init();
	trail->Init();
	battleStartTelop->Init();
	stageClearTelop->Init();
	telopBG->Init();
}

//=============================================================================
// �I������
//=============================================================================
void GameSceneUI::Uninit(void)
{
	combo->Uninit();
	cursor->Uninit();
	guage->Uninit();
	line->Uninit();
	score->Uninit();
	star->Uninit();
	trail->Uninit();
	battleStartTelop->Uninit();
	stageClearTelop->Uninit();
	telopBG->Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void GameSceneUI::Update(HWND hWnd)
{
	combo->Update();
	cursor->Update(hWnd);
	guage->Update();
	line->Update();
	score->Update();
	star->Update();
	trail->Update();
	battleStartTelop->Update();
	stageClearTelop->Update();
	telopBG->Update();

#ifdef _DEBUG
	// �f�o�b�O�p�R�}���h
	if (GetKeyboardTrigger(DIK_1))
	{
		guage->ChangeGuage(-10);
	}
	if (GetKeyboardTrigger(DIK_2))
	{
		guage->ChangeGuage(10);
	}
	if (GetKeyboardTrigger(DIK_3))
	{
		comboManager->AddCombo(1);
	}
	if (GetKeyboardTrigger(DIK_4))
	{
		score->AddScore(1000);
	}
	if (GetKeyboardTrigger(DIK_5))
	{
		comboManager->SetCombo(0);
	}
	if (GetKeyboardTrigger(DIK_6))
	{
		battleStartTelop->SetBattleStartTelop();
	}
	if (GetKeyboardTrigger(DIK_7))
	{
		stageClearTelop->SetStageClearTelop();
	}
#endif
}

//=============================================================================
// �`�揈��
//=============================================================================
void GameSceneUI::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, true);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	combo->Draw();
	cursor->Draw();
	guage->Draw();
	line->Draw();
	score->Draw();
	star->Draw();
	trail->Draw();
	battleStartTelop->Draw();
	stageClearTelop->Draw();
	telopBG->Draw();

	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, false);
}

