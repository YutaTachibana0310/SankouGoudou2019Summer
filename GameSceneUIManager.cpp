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
#include "starButtonUI.h"
#include "comboUI.h"
#include "trailUI.h"
#include "cursorUI.h"
#include "battleStartTelop.h"
#include "stageClearTelop.h"
#include "telopBG.h"
#include "bomberStockUI.h"
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
	starButton = new StarButton();
	cursor = new Cursor();
	combo = new Combo();
	guage = new Guage();
	score = new Score();
	trail = new Trail();
	battleStartTelop = new BattleStartTelop();
	stageClearTelop = new StageClearTelop();
	telopBG = new TelopBG();
	bomberStock = new BomberStock();
}

//*****************************************************************************
// �f�X�g���N�^
//*****************************************************************************
GameSceneUIManager::~GameSceneUIManager()
{
	SAFE_DELETE(combo);
	SAFE_DELETE(cursor);
	SAFE_DELETE(guage);
	SAFE_DELETE(score);
	SAFE_DELETE(starButton);
	SAFE_DELETE(trail);
	SAFE_DELETE(battleStartTelop);
	SAFE_DELETE(stageClearTelop);
	SAFE_DELETE(telopBG);
	SAFE_DELETE(bomberStock);
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
	score->Update();
	starButton->Update(hWnd);
	trail->Update();
	battleStartTelop->Update();
	stageClearTelop->Update();
	telopBG->Update();
	bomberStock->Update();

#if 0
	// �f�o�b�O�p�R�}���h
	if (GetKeyboardTrigger(DIK_1))
	{
		AddCombo(1);
	}
	if (GetKeyboardTrigger(DIK_2))
	{
		AddScore(1);
	}
	if (GetKeyboardTrigger(DIK_3))
	{
		SetStageClearTelop();
	}
	if (GetKeyboardTrigger(DIK_4))
	{
		SetBattleStartTelop();
	}
	if (GetKeyboardTrigger(DIK_5))
	{
		SetHPGuage(0.5f);
	}
	if (GetKeyboardTrigger(DIK_6))
	{
		SetBomberStock(3);
	}

	if (GetKeyboardTrigger(DIK_7))
	{
		SetBomberStock(4);
	}
#endif

	guage->Update();

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
	score->Draw();
	starButton->Draw();
	trail->Draw();
	bomberStock->Draw();
	telopBG->Draw();
	battleStartTelop->Draw();
	stageClearTelop->Draw();

	cursor->Draw();

	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, false);
}


//=============================================================================
// �J�[�\���̐F�X�V���菈��
//=============================================================================
bool GameSceneUIManager::IsStarCursorOvered()
{
	std::vector<D3DXVECTOR3> starButtonPos;
	GetStarPosition(starButtonPos);

	// �ǂ̃X�^�[�Ƃ��������ĂȂ�������false,����ȊO��true
	if (cursor->IsCursorOvered(starButtonPos[0], COLLIDERSIZE_STAR))
		return true;

	if (cursor->IsCursorOvered(starButtonPos[1], COLLIDERSIZE_STAR))
		return true;

	if (cursor->IsCursorOvered(starButtonPos[2], COLLIDERSIZE_STAR))
		return true;

	if (cursor->IsCursorOvered(starButtonPos[3], COLLIDERSIZE_STAR))
		return true;

	if (cursor->IsCursorOvered(starButtonPos[4], COLLIDERSIZE_STAR))
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
	starButton->GetStarButtonPosition(out);
}

//=============================================================================
// �X�^�[�{�^�����͊m�F
//=============================================================================
int GameSceneUIManager::IsStarSelected()
{
	std::vector<D3DXVECTOR3> starButtonPos;
	GetStarPosition(starButtonPos);

	for (int i = 0; i < 5; i++)
	{
		if (cursor->IsCursorOvered(starButtonPos[i], COLLIDERSIZE_STAR))
			return i;
	}

	return 5;
}

//=============================================================================
// HP�Q�[�W�Z�b�g����(�����ŗ^����ꂽ����(0.0f�`1.0f)�ɃQ�[�W���Z�b�g����)
//=============================================================================
void GameSceneUIManager::SetHPGuage(float percentage)
{
	guage->trueGuagePercentage = percentage;
}

//=============================================================================
// �{���X�g�b�N�Z�b�g����(�����ŗ^����ꂽ�����{���o�[�X�g�b�N���Z�b�g����)
//=============================================================================
void GameSceneUIManager::SetBomberStock(int stockedBomNum, bool isCharging)
{
	//*���ӁF���͉���max3�ɂ��Ă܂��B
	if (stockedBomNum > MAX_STOCKED_BOM_NUM)
	{
		//�������j��΍�
		return;
	}

	bomberStock->stockedBomNum = stockedBomNum;
	bomberStock->isCharging = isCharging;
}
