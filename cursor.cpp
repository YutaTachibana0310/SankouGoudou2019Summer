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
#include "collider.h"
#include "star.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define SIZE_X_CURSOR			(40.0f)
#define SIZE_Y_CURSOR			(40.0f)
#define SPEED_ROTATION			(0.10f)

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
	cursor.size = D3DXVECTOR3(SIZE_X_CURSOR, SIZE_Y_CURSOR, 0.0f);
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
// �I������Ă��邩�̔��菈�� (����������I�����) (*�C���\��)
//=============================================================================
bool IsStarHitted(int num, HWND hWnd)
{
	D3DXVECTOR3 starPosition[STAR_MAX];
	GetStarPosition(starPosition);

	// �ǂ̃X�^�[�Ƃ��������ĂȂ�������false,����ȊO��true
	if (IsHittedBB(GetMousePosition(hWnd), starPosition[0],
		D3DXVECTOR2(COLLIDERSIZE_X_STAR, COLLIDERSIZE_Y_STAR),
		D3DXVECTOR2(COLLIDERSIZE_X_CURSOR, COLLIDERSIZE_Y_CURSOR)))
		return true;

	if (IsHittedBB(GetMousePosition(hWnd), starPosition[1],
		D3DXVECTOR2(COLLIDERSIZE_X_STAR, COLLIDERSIZE_Y_STAR),
		D3DXVECTOR2(COLLIDERSIZE_X_CURSOR, COLLIDERSIZE_Y_CURSOR)))
		return true;

	if (IsHittedBB(GetMousePosition(hWnd), starPosition[2],
		D3DXVECTOR2(COLLIDERSIZE_X_STAR, COLLIDERSIZE_Y_STAR),
		D3DXVECTOR2(COLLIDERSIZE_X_CURSOR, COLLIDERSIZE_Y_CURSOR)))
		return true;

	if (IsHittedBB(GetMousePosition(hWnd), starPosition[3],
		D3DXVECTOR2(COLLIDERSIZE_X_STAR, COLLIDERSIZE_Y_STAR),
		D3DXVECTOR2(COLLIDERSIZE_X_CURSOR, COLLIDERSIZE_Y_CURSOR)))
		return true;

	if (IsHittedBB(GetMousePosition(hWnd), starPosition[4],
		D3DXVECTOR2(COLLIDERSIZE_X_STAR, COLLIDERSIZE_Y_STAR),
		D3DXVECTOR2(COLLIDERSIZE_X_CURSOR, COLLIDERSIZE_Y_CURSOR)))
		return true;

	return false;
}