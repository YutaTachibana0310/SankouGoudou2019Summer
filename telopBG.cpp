//=============================================================================
//
// �e���b�v�w�i���� [telopBG.cpp]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "telopBG.h"
#include "Framework/Easing.h"
#include "debugWindow.h"
#include "battleStartTelop.h"
#include "UIdrawer.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define SIZE_TELOP_BG		(D3DXVECTOR3(SCREEN_WIDTH/4,50.0f,0.0f))
#define POSITION_TELOP_BG	(D3DXVECTOR3(SCREEN_WIDTH/2,SCREEN_HEIGHT/10*8,0.0f))
#define INITIALVALUE_BG_PERCENTAGE (0.0f)
#define DURATION_OPEN_CLOSE (20.0f)

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
bool telopBGOpenActivated = false;
bool telopBGCloseActivated = false;

//*****************************************************************************
// �R���X�g���N�^
//*****************************************************************************
TelopBG::TelopBG()
{
	telopBG = new Object();

	telopBG->LoadTexture("data/TEXTURE/UI/Telop/telopBG.png");
	telopBG->MakeVertex();

	telopBG->position = POSITION_TELOP_BG;
	telopBG->size = SIZE_TELOP_BG;
	telopBG->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	telopBG->SetColorObject(SET_COLOR_NOT_COLORED);

	percentage = INITIALVALUE_BG_PERCENTAGE;
}

//*****************************************************************************
// �f�X�g���N�^
//*****************************************************************************
TelopBG::~TelopBG()
{
	SAFE_DELETE(telopBG);
}

//=============================================================================
// �X�V����
//=============================================================================
void TelopBG::Update(void)
{
	//�@���ӂ�h�~
	if (percentage < 0)
	{
		percentage = 0;
	}
	if (percentage > 1.0f)
	{
		percentage = 1.0f;
	}

	if (telopBGOpenActivated)
	{
		OpenTelopBG();
	}

	if (telopBGCloseActivated)
	{
		CloseTelopBG();
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void TelopBG::Draw(void)
{
	telopBG->Draw();
	SetVertex(percentage);
}

//=============================================================================
// �I�u�W�F�N�g�̒��_���W�̐ݒ�@�i�e���b�v�w�i��p�j
//=============================================================================
void TelopBG::SetVertex(float percentage)
{
	// ���_���W�̐ݒ�
	telopBG->vertexWk[0].vtx = D3DXVECTOR3(0, telopBG->position.y -telopBG->size.y*percentage, telopBG->position.z);
	telopBG->vertexWk[1].vtx = D3DXVECTOR3(SCREEN_WIDTH, telopBG->position.y -telopBG->size.y*percentage, telopBG->position.z);
	telopBG->vertexWk[2].vtx = D3DXVECTOR3(0, telopBG->position.y +telopBG->size.y*percentage, telopBG->position.z);
	telopBG->vertexWk[3].vtx = D3DXVECTOR3(SCREEN_WIDTH, telopBG->position.y +telopBG->size.y*percentage, telopBG->position.z);
}

//=============================================================================
// �w�i���J������
//=============================================================================
void TelopBG::OpenTelopBG(void)
{
	SetEasingValueTelopBGOpen();
	percentage = Easing::EaseValue(telopBG->GetCountObject(DURATION_OPEN_CLOSE), easingStart, easingGoal, InOutCubic);

	if(percentage >= easingGoal)
	{
		telopBGOpenActivated = false;
		percentage = 1.0f;
		telopBG->countFrame = 0;
	}
}

//=============================================================================
// �w�i����鏈��
//=============================================================================
void TelopBG::CloseTelopBG(void)
{
	SetEasingValueTelopBGClose();
	percentage = Easing::EaseValue(telopBG->GetCountObject(DURATION_OPEN_CLOSE), easingStart, easingGoal, InOutCubic);

	if(percentage <= easingGoal)
	{
		telopBGCloseActivated = false;
		percentage = 0.0f;
		telopBG->countFrame = 0;
	}
}

//=============================================================================
// �w�iopen�C�[�W���O�Z�b�g����
//=============================================================================
void TelopBG::SetEasingValueTelopBGOpen(void)
{	
	easingStart = INITIALVALUE_BG_PERCENTAGE;
	easingGoal = 1.0f;
}

//=============================================================================
// �w�iclose�C�[�W���O�Z�b�g����
//=============================================================================
void TelopBG::SetEasingValueTelopBGClose(void)
{
	easingStart = 1.0f;
	easingGoal = INITIALVALUE_BG_PERCENTAGE;
}

//=============================================================================
// �e���b�v�w�i�J�n�A�N�e�B�x�[�g����
//=============================================================================
void TelopBG::AvctivateTelopBGOpen(void)
{
	telopBGOpenActivated = true;
}

//=============================================================================
// �e���b�v�w�i�I���A�N�e�B�x�[�g����
//=============================================================================
void TelopBG::AvctivateTelopBGClose(void)
{
	telopBGCloseActivated = true;
}

//=============================================================================
// �e���b�v�w�i�J�n�A�N�e�B�u��Ԏ擾����
//=============================================================================
bool TelopBG::GetTelopBGOpenActive(void)
{
	return telopBGOpenActivated;
}

//=============================================================================
// �e���b�v�w�i�I���A�N�e�B�u��Ԏ擾����
//=============================================================================
bool TelopBG::GetTelopBGCloseActive(void)
{
	return telopBGCloseActivated;
}