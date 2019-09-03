//=============================================================================
//
// Game�V�[��UI�Ǘ����� [GameSceneUIManagerManager.cpp]
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
//GameSceneUIManager *gameSceneUI[GAME_SCENE_UI_MAX];

//*****************************************************************************
// �R���X�g���N�^
//*****************************************************************************
GameSceneUIManager::GameSceneUIManager()
{
	line = new Line();
	star = new Star();
	cursor = new Cursor();
	combo = new Combo();
	guage = new Guage();
	score = new Score();
	trail = new Trail();
	battleStartTelop = new BattleStartTelop();
	stageClearTelop = new StageClearTelop();
	telopBG = new TelopBG();
}

//*****************************************************************************
// �f�X�g���N�^
//*****************************************************************************
GameSceneUIManager::~GameSceneUIManager()
{
	delete combo;
	combo = NULL;

	delete cursor;
	cursor = NULL;

	delete guage;
	guage = NULL;

	delete line;
	line = NULL;

	delete score;
	score = NULL;

	delete star;
	star = NULL;

	delete trail;
	trail = NULL;

	delete battleStartTelop;
	battleStartTelop = NULL;

	delete stageClearTelop;
	stageClearTelop = NULL;

	delete telopBG;
	telopBG = NULL;
}

//=============================================================================
// ����������
//=============================================================================
void GameSceneUIManager::Init()
{
}

//=============================================================================
// �I������
//=============================================================================
void GameSceneUIManager::Uninit()
{

}


//=============================================================================
// �X�V����
//=============================================================================
void GameSceneUIManager::Update(HWND hWnd)
{
	combo->Update();
	cursor->Update(hWnd);
	guage->Update();
	line->Update();
	score->Update();
	star->Update(hWnd);
	trail->Update();
	battleStartTelop->Update();
	stageClearTelop->Update();
	telopBG->Update();

#ifdef _DEBUG
	// �f�o�b�O�p�R�}���h
	if (GetKeyboardTrigger(DIK_1))
	{
	}
	if (GetKeyboardTrigger(DIK_2))
	{
	}
	if (GetKeyboardTrigger(DIK_3))
	{
	}
	if (GetKeyboardTrigger(DIK_4))
	{
	}
	if (GetKeyboardTrigger(DIK_5))
	{
	}
	if (GetKeyboardTrigger(DIK_6))
	{
	}
	if (GetKeyboardTrigger(DIK_7))
	{
	}
#endif

	UpdateCursorColor();
}

//=============================================================================
// �`�揈��
//=============================================================================
void GameSceneUIManager::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, true);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	combo->Draw();
	guage->Draw();
	line->Draw();
	score->Draw();
	star->Draw();
	trail->Draw();
	battleStartTelop->Draw();
	stageClearTelop->Draw();
	telopBG->Draw();

	cursor->Draw();

	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, false);
}


//=============================================================================
// �J�[�\���̐F�X�V���菈��
//=============================================================================
bool GameSceneUIManager::IsStarCursorOvered()
{
	D3DXVECTOR3 starPosition[5];
	SetStarPosition(starPosition);

	// �ǂ̃X�^�[�Ƃ��������ĂȂ�������false,����ȊO��true
	if (cursor->IsCursorOvered(starPosition[0], COLLIDERSIZE_STAR))
		return true;

	if (cursor->IsCursorOvered(starPosition[1], COLLIDERSIZE_STAR))
		return true;

	if (cursor->IsCursorOvered(starPosition[2], COLLIDERSIZE_STAR))
		return true;

	if (cursor->IsCursorOvered(starPosition[3], COLLIDERSIZE_STAR))
		return true;

	if (cursor->IsCursorOvered(starPosition[4], COLLIDERSIZE_STAR))
		return true;

	return false;
}

//=============================================================================
// �J�[�\���̐F�X�V����
//=============================================================================
void GameSceneUIManager::UpdateCursorColor()
{
	if (IsStarCursorOvered())
	{
		// �I������Ă���Ȃ�
		cursor->PaintCursorRed();
	}
	else
	{	// ���ɖ߂�
		cursor->PaintCursorYellow();
	}
}