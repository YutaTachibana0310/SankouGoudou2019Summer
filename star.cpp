//=============================================================================
//
// �X�^�[��ʏ��� [star.cpp]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "star.h"
#include "UIdrawer.h"
#include "collider.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

#define NUMBER_ROTATION		(1)
#define SIZE_X_STAR			(100.0f)
#define SIZE_Y_STAR			(100.0f)
#define COLLIDERSIZE_X_STAR (120.0f)
#define COLLIDERSIZE_Y_STAR (120.0f)
#define VOLUME_ZOOM			(30.0f)
#define SPEED_ROTATION		(0.1f)

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void RotateStar(int num);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
OBJECT	star[STAR_MAX];

//=============================================================================
// ����������
//=============================================================================
HRESULT InitStar(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int i = 0; i < STAR_MAX; i++)
	{
		LoadTexture(pDevice, ADRESS_TEXTURE_STAR, &star[i]);
		CreateObjectCircle(&star[i], star[i].size.x, star[i].size.y);
		InitialTexture(&star[i]);
		MakeVertexRotateObject(&star[i]);

		// ���W�ݒ�
		star[TOP].position			= POSITION_STAR_TOP;
		star[MIDDLE_LEFT].position  = POSITION_STAR_MIDDLE_LEFT;
		star[LOWER_LEFT].position   = POSITION_STAR_LOWER_LEFT;
		star[LOWER_RIGHT].position	= POSITION_STAR_LOWER_RIGHT;
		star[MIDDLE_RIGHT].position = POSITION_STAR_MIDDLE_RIGHT;

		star[i].size				= D3DXVECTOR3(SIZE_X_STAR, SIZE_Y_STAR, 0.0f);
		star[i].colliderSize		= D3DXVECTOR3(COLLIDERSIZE_X_STAR, COLLIDERSIZE_X_STAR, 0.0f);
		star[i].rotation			= D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//�@�F�ݒ�
		SetColorObject(&star[TOP],			SET_COLOR_YELLOW);
		SetColorObject(&star[MIDDLE_LEFT],	SET_COLOR_PINK);
		SetColorObject(&star[LOWER_LEFT],	SET_COLOR_RIGHTBLUE);
		SetColorObject(&star[LOWER_RIGHT],	SET_COLOR_RED);
		SetColorObject(&star[MIDDLE_RIGHT],	SET_COLOR_GREEN);
	}

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitStar(void)
{
	for (int i = 0; i < STAR_MAX; i++)
	{
		ReleaseTexture(&star[i]);
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateStar(HWND hWnd)
{
	for (int i = 0; i < STAR_MAX; i++)
	{
			if (IsSelected(i,hWnd))
			{
				if (IsMouseLeftTriggered())
				{
					star[i].rotateUsed = true;
				}
				star[i].size.x = SIZE_X_STAR + VOLUME_ZOOM;
				star[i].size.y = SIZE_Y_STAR + VOLUME_ZOOM;
			}
			else
			{
				star[i].size.x = SIZE_X_STAR;
				star[i].size.y = SIZE_Y_STAR;
			}

		CreateObjectCircle(&star[i], star[i].size.x, star[i].size.y);
		RotateStar(i);
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawStar(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int i = 0; i < STAR_MAX; i++)
	{
		DrawObject(pDevice, star[i]);
		SetVertexRotateObject(&star[i]);
	}
}

//=============================================================================
// ��]����
//=============================================================================
void RotateStar(int num)
{
	if (star[num].rotateUsed == true && star[num].rotation.z < D3DXToRadian(360.0f) * NUMBER_ROTATION)
	{
		star[num].rotation.z += SPEED_ROTATION *D3DX_PI;
	}
	if (star[num].rotation.z >= D3DXToRadian(360.0f) * NUMBER_ROTATION)
	{
		star[num].rotation.z = 0.0f;
		star[num].rotateUsed = false;
	}
}

//=============================================================================
// �I������Ă��邩�̔��菈�� (����������I�����)
//=============================================================================
bool IsSelected(int num, HWND hWnd)
{
	return IsHittedBB(GetMousePosition(hWnd),star[num].position,
		D3DXVECTOR2(star[num].colliderSize.x,star[num].colliderSize.y), 
		D3DXVECTOR2(COLLIDERSIZE_X_CURSOR,COLLIDERSIZE_Y_CURSOR));
}

//=============================================================================
// �����W�擾�p�i�n糒ǋL�j
//=============================================================================
void GetStarPosition(D3DXVECTOR3 *pos) {
	for (int i = 0; i < STAR_MAX; i++)
	{
		pos[i] = star[i].position;
	}
}
