//=============================================================================
//
// �J�[�\����ʏ��� [cursor.cpp]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "cursor.h"
#include "UIdrawer.h"
#include "star.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define SIZE_CURSOR		(D3DXVECTOR3(40.0f,40.0f,0.0f))
#define SPEED_ROTATION	(0.10f)

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
OBJECT	cursor;
bool	IsStarHitted(int num, HWND hWnd);

//=============================================================================
// ����������
//=============================================================================
HRESULT InitCursor(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	LoadTexture(pDevice, ADRESS_TEXTURE_CURSOR, &cursor);
	InitialTexture(&cursor);
	MakeVertexRotateObject(&cursor);

	cursor.position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	cursor.size		= SIZE_CURSOR;
	cursor.rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	SetColorObject(&cursor, SET_COLOR_YELLOW);

	// ��]�I�u�W�F�N�g�p�̃T�[�N�����쐬
	CreateObjectCircle(&cursor, cursor.size.x, cursor.size.y);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitCursor(void)
{
	ReleaseTexture(&cursor);
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateCursor(HWND hWnd)
{
	cursor.position = GetMousePosition(hWnd);

	for (int i = 0; i < STAR_MAX; i++)
	{
		if (IsStarHitted(i, hWnd))
		{
			// �I������Ă���Ȃ�
			SetColorObject(&cursor, SET_COLOR_RED);
		}
		else
		{	// ���ɖ߂�
			SetColorObject(&cursor, SET_COLOR_YELLOW);
		}
	}

	cursor.rotation.z -= SPEED_ROTATION;
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawCursor(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	DrawObject(pDevice, cursor);
	SetVertexRotateObject(&cursor);
}

//=============================================================================
// �I������Ă��邩�̔��菈�� (����������I�����)
//=============================================================================
bool IsStarHitted(int num, HWND hWnd)
{
	D3DXVECTOR3 starPosition[STAR_MAX];
	GetStarPosition(starPosition);

	// �ǂ̃X�^�[�Ƃ��������ĂȂ�������false,����ȊO��true
	if (IsCursorOverd(hWnd, starPosition[0], COLLIDERSIZE_STAR))
		return true;

	if (IsCursorOverd(hWnd, starPosition[1], COLLIDERSIZE_STAR))
		return true;

	if (IsCursorOverd(hWnd, starPosition[2], COLLIDERSIZE_STAR))
		return true;

	if (IsCursorOverd(hWnd, starPosition[3], COLLIDERSIZE_STAR))
		return true;

	if (IsCursorOverd(hWnd, starPosition[4], COLLIDERSIZE_STAR))
		return true;

	return false;
}

//=============================================================================
// �J�[�\�����d�Ȃ������̔��菈��
//=============================================================================
bool IsCursorOverd(HWND hWnd,D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	size /= 2.0f;	// ���T�C�Y�ɂ���

	D3DXVECTOR3 cursorSize = COLLIDERSIZE_CURSOR / 2;

	if (GetMousePosition(hWnd).x + cursorSize.x > pos.x - size.x 
		&& pos.x + size.x > GetMousePosition(hWnd).x - cursorSize.x 
		&&
		GetMousePosition(hWnd).y + cursorSize.y > pos.y - size.y 
		&& pos.y + size.y > GetMousePosition(hWnd).y - cursorSize.y)
	{
		return true;
	}

	return false;
}
