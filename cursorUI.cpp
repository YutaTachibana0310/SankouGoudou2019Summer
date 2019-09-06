//=============================================================================
//
// �J�[�\����ʏ��� [outerCircle.cpp]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "UIdrawer.h"
#include "GameSceneUIManager.h"
#include "cursorUI.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define SIZE_CURSOR		(D3DXVECTOR3(45.0f,45.0f,0.0f))
#define SPEED_ROTATION	(0.10f)
#define COLLIDERSIZE_CURSOR (D3DXVECTOR3(5.0f,5.0f,0.0f))

//*****************************************************************************
// �R���X�g���N�^
//*****************************************************************************
Cursor::Cursor()
{
	//�O���̃T�[�N��
	outerCircle = new RotateObject();
	outerCircle->LoadTexture("data/TEXTURE/UI/Cursor/outerCircle.png");
	outerCircle->MakeVertex();
	outerCircle->position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	outerCircle->size = SIZE_CURSOR;
	outerCircle->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	outerCircle->colliderSize = COLLIDERSIZE_CURSOR / 2;
	outerCircle->SetColorObject(SET_COLOR_NOT_COLORED);
	outerCircle->CreateObjectCircle();

	//�����̃T�[�N��
	innerCircle = new RotateObject();
	innerCircle->LoadTexture("data/TEXTURE/UI/Cursor/innerCircle.png");
	innerCircle->MakeVertex();
	innerCircle->position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	innerCircle->size = SIZE_CURSOR;
	innerCircle->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	innerCircle->colliderSize = COLLIDERSIZE_CURSOR / 2;
	innerCircle->SetColorObject(SET_COLOR_NOT_COLORED);
	innerCircle->CreateObjectCircle();
}

//*****************************************************************************
// �f�X�g���N�^
//*****************************************************************************
Cursor::~Cursor()
{
	delete outerCircle;
	outerCircle = NULL;

	delete innerCircle;
	innerCircle = NULL;
}

//=============================================================================
// �X�V����
//=============================================================================
void Cursor::Update(HWND hWnd)
{
	outerCircle->position = GetMousePosition(hWnd);
	outerCircle->rotation.z -= SPEED_ROTATION;

	innerCircle->position = GetMousePosition(hWnd);
	innerCircle->rotation.z += SPEED_ROTATION;
}

//=============================================================================
// �`�揈��
//=============================================================================
void Cursor::Draw(void)
{
	outerCircle->Draw();
	outerCircle->SetVertex();

	innerCircle->Draw();
	innerCircle->SetVertex();
}

//=============================================================================
// �J�[�\�����d�Ȃ������̔��菈��(�O���̃T�[�N���Ƃ̓����蔻��)
//=============================================================================
bool Cursor::IsCursorOvered(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	size /= 2.0f;	// ���T�C�Y�ɂ���

	if (outerCircle->position.x +outerCircle->colliderSize.x > pos.x - size.x 
		&& pos.x + size.x > outerCircle->position.x -outerCircle->colliderSize.x 
		&& outerCircle->position.y +outerCircle->colliderSize.y > pos.y - size.y 
		&& pos.y + size.y > outerCircle->position.y -outerCircle->colliderSize.y)
	{
		return true;
	}

	return false;
}

//*****************************************************************************
// �{�^���I����ԂɐF�X�V
//*****************************************************************************
void Cursor::PaintCursorRed()
{
	outerCircle->SetColorObject(SET_COLOR_RED);
	innerCircle->SetColorObject(SET_COLOR_RED);
}

//*****************************************************************************
// ��{�^���I����ԂɐF�X�V
//*****************************************************************************
void Cursor::PaintCursorYellow()
{
	outerCircle->SetColorObject(SET_COLOR_NOT_COLORED);
	innerCircle->SetColorObject(SET_COLOR_NOT_COLORED);
}
