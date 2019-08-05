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
#include "starUI.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define SIZE_CURSOR		(D3DXVECTOR3(40.0f,40.0f,0.0f))
#define SPEED_ROTATION	(0.10f)

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************

//=============================================================================
// ����������
//=============================================================================
void Cursor::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	LoadTexture(pDevice, ADRESS_TEXTURE_CURSOR);
	InitialTexture();
	MakeVertexRotateObject();

	position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	size		= SIZE_CURSOR;
	rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	colliderSize = COLLIDERSIZE_CURSOR / 2;

	SetColorObject(SET_COLOR_YELLOW);

	// ��]�I�u�W�F�N�g�p�̃T�[�N�����쐬
	CreateObjectCircle();
}

//=============================================================================
// �I������
//=============================================================================
void Cursor::Uninit(void)
{
	ReleaseTexture();
}

//=============================================================================
// �X�V����
//=============================================================================
void Cursor::Update(HWND hWnd)
{
	position = GetMousePosition(hWnd);

	for (int i = 0; i < STAR_MAX; i++)
	{
		if (IsStarHitted(i))
		{
			// �I������Ă���Ȃ�
			SetColorObject(SET_COLOR_RED);
		}
		else
		{	// ���ɖ߂�
			SetColorObject(SET_COLOR_YELLOW);
		}
	}

	rotation.z -= SPEED_ROTATION;
}

//=============================================================================
// �`�揈��
//=============================================================================
void Cursor::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	DrawObject(pDevice);
	SetVertexRotateObject();
}

//=============================================================================
// �I������Ă��邩�̔��菈�� (����������I�����)
//=============================================================================
bool Cursor::IsStarHitted(int num)
{
	D3DXVECTOR3 starPosition[STAR_MAX];
	GetStarPosition(starPosition);

	// �ǂ̃X�^�[�Ƃ��������ĂȂ�������false,����ȊO��true
	if (IsCursorOvered(starPosition[0], COLLIDERSIZE_STAR))
		return true;

	if (IsCursorOvered(starPosition[1], COLLIDERSIZE_STAR))
		return true;

	if (IsCursorOvered(starPosition[2], COLLIDERSIZE_STAR))
		return true;

	if (IsCursorOvered(starPosition[3], COLLIDERSIZE_STAR))
		return true;

	if (IsCursorOvered(starPosition[4], COLLIDERSIZE_STAR))
		return true;

	return false;
}

//=============================================================================
// �J�[�\�����d�Ȃ������̔��菈��
//=============================================================================
bool Cursor::IsCursorOvered(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	size /= 2.0f;	// ���T�C�Y�ɂ���

	if (position.x + colliderSize.x > pos.x - size.x 
		&& pos.x + size.x > position.x - colliderSize.x 
		&&
		position.y + colliderSize.y > pos.y - size.y 
		&& pos.y + size.y > position.y - colliderSize.y)
	{
		return true;
	}

	return false;
}
