//=============================================================================
//
// �J�[�\����ʏ��� [cursor.cpp]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "cursorUI.h"
#include "UIdrawer.h"
#include "GameSceneUIManager.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define SIZE_CURSOR		(D3DXVECTOR3(40.0f,40.0f,0.0f))
#define SPEED_ROTATION	(0.10f)
#define COLLIDERSIZE_CURSOR (D3DXVECTOR3(5.0f,5.0f,0.0f))

//*****************************************************************************
// �R���X�g���N�^
//*****************************************************************************
Cursor::Cursor()
{
	cursor = new RotateObject();
	cursor->LoadTexture("data/TEXTURE/UI/cursor.png");
	cursor->MakeVertex();

	cursor->position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	cursor->size = SIZE_CURSOR;
	cursor->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	cursor->colliderSize = COLLIDERSIZE_CURSOR / 2;

	cursor->SetColorObject(SET_COLOR_YELLOW);

	// ��]�I�u�W�F�N�g�p�̃T�[�N�����쐬
	cursor->CreateObjectCircle();
}

//*****************************************************************************
// �f�X�g���N�^
//*****************************************************************************
Cursor::~Cursor()
{
	delete cursor;
	cursor = NULL;
}

//=============================================================================
// �X�V����
//=============================================================================
void Cursor::Update(HWND hWnd)
{
	cursor->position = GetMousePosition(hWnd);
	cursor->rotation.z -= SPEED_ROTATION;
}

//=============================================================================
// �`�揈��
//=============================================================================
void Cursor::Draw(void)
{
	cursor->Draw();
	cursor->SetVertex();
}

//=============================================================================
// �J�[�\�����d�Ȃ������̔��菈��
//=============================================================================
bool Cursor::IsCursorOvered(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	size /= 2.0f;	// ���T�C�Y�ɂ���

	if (cursor->position.x +cursor->colliderSize.x > pos.x - size.x 
		&& pos.x + size.x > cursor->position.x -cursor->colliderSize.x 
		&& cursor->position.y +cursor->colliderSize.y > pos.y - size.y 
		&& pos.y + size.y > cursor->position.y -cursor->colliderSize.y)
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
	cursor->SetColorObject(SET_COLOR_RED);
}

//*****************************************************************************
// ��{�^���I����ԂɐF�X�V
//*****************************************************************************
void Cursor::PaintCursorYellow()
{
	cursor->SetColorObject(SET_COLOR_YELLOW);
}
