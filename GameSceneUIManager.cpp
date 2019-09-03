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
	std::vector<D3DXVECTOR3> starPos;
	GetStarPosition(starPos);

	// �ǂ̃X�^�[�Ƃ��������ĂȂ�������false,����ȊO��true
	if (cursor->IsCursorOvered(starPos[0], COLLIDERSIZE_STAR))
		return true;

	if (cursor->IsCursorOvered(starPos[1], COLLIDERSIZE_STAR))
		return true;

	if (cursor->IsCursorOvered(starPos[2], COLLIDERSIZE_STAR))
		return true;

	if (cursor->IsCursorOvered(starPos[3], COLLIDERSIZE_STAR))
		return true;

	if (cursor->IsCursorOvered(starPos[4], COLLIDERSIZE_STAR))
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


//=============================================================================
// �R���{�̉��Z�i�����Ŏ󂯎�����l���R���{�ɉ��Z����j
//=============================================================================
void  GameSceneUIManager::AddCombo(int value)
{
	combo->combo += value;

	if (value > 0)
	{
		combo->volumeUpEffectUsed = true;
	}
}
//=============================================================================
// �R���{�̃Z�b�g
//=============================================================================
void  GameSceneUIManager::SetCombo(int num)
{
	num = combo->combo;
}

//=============================================================================
// �R���{�̃��Z�b�g
//=============================================================================
void GameSceneUIManager::ReSetCombo(void)
{
	combo->combo = 0;
}

//=============================================================================
// �X�R�A�̉��Z�i�����Ŏ󂯎�����l���X�R�A�ɉ��Z����j
//=============================================================================
void  GameSceneUIManager::AddScore(int value)
{
	score->score += value;

	// �X�R�A�����Z���ꂽ��s������
	if (value > 0)
	{
		// �G�t�F�N�g�L����
		score->volumeUpEffectUsed = true;
	}
}

//=============================================================================
// �X�R�A�̃Z�b�g
//=============================================================================
void  GameSceneUIManager::SetScore(int num)
{
	num = score->score;
}

//=============================================================================
// HP�̉��Z�i�����Ŏ󂯎�����l��HO�ɉ��Z����j
//=============================================================================
void  GameSceneUIManager::AddHp(float value)
{
	guage->trueGuagePercentage += (value /= guage->maxHp);
}

//=============================================================================
// �X�e�[�W�N���A�e���b�v�Z�b�g����
//=============================================================================
void  GameSceneUIManager::SetStageClearTelop(void)
{
	stageClearTelop->isStageClearTelopActivated = true;
}

//=============================================================================
// �o�g���X�^�[�g�e���b�v�Z�b�g����
//=============================================================================
void  GameSceneUIManager::SetBattleStartTelop(void)
{
	battleStartTelop->isBattleStartTelopActivated = true;
}

//=============================================================================
// �X�^�[���W�Q�b�g����
//=============================================================================
void  GameSceneUIManager::GetStarPosition(std::vector<D3DXVECTOR3>& out)
{
	star->GetStarPosition(out);
}

//=============================================================================
// �X�^�[���W�Z�b�g����
//=============================================================================
void  GameSceneUIManager::SetStarPosition(D3DXVECTOR3* pos)
{
	//pos = star->GetStarPosition();
}
