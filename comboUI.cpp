//=============================================================================
//
// �R���{���� [combo.cpp]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#include "main.h"
#include "comboUI.h"
#include "UIdrawer.h"
#include "input.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define COMBOPARTS_MAX		(3)
#define	INTERVAL_NUMBER		(80.0f)			// �R���{�����̕\���Ԋu
#define	INTERVAL_NUMBER_TEXTURE	(0.097f)	// �e�N�X�`�����R���{�����̕\���Ԋu
#define	PLACE_MAX			(2)				// �R���{�̌���
#define BASE_NUMBER			(10)			// �i��
#define VOLUME_ZOOM			(50.0f)
#define ROTATION_SPEED_COMBO_BACKGROUND (0.01f)

// �T�C�Y��`
#define SIZE_NUMBER_COMBO		(D3DXVECTOR3(40.0f,75.0f,0.0f))
#define SIZE_TEXT_COMBO			(D3DXVECTOR3(45.0f,20.0f,0.0f))
#define SIZE_BACKGROUND_COMBO	(D3DXVECTOR3(200.0f,200.0f,0.0f))

// ���W��`
#define POSITION_NUMBER_COMBO		(D3DXVECTOR3(SCREEN_WIDTH / 10*2.0f, SCREEN_HEIGHT / 10*2.0f , 0.0f))
#define POSITION_TEXT_COMBO			(D3DXVECTOR3(SCREEN_WIDTH / 10*3.2f, SCREEN_HEIGHT / 10*2.3f , 0.0f))
#define POSITION_BACKGROUND_COMBO	(D3DXVECTOR3(SCREEN_WIDTH / 10*2.25f, SCREEN_HEIGHT / 10*2.0f , 0.0f))

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
static void VolumeUpEffect(void);
void UpdateNumberColor(void);

//*****************************************************************************
// �O���[�o���ϐ��錾
//*****************************************************************************
OBJECT	comboParts[COMBOPARTS_MAX];
int		g_combo;	// �R���{
int		g_combo_max;
static float radian;
static bool	volumeUpEffectUsed;

//=============================================================================
// ����������
//=============================================================================
HRESULT InitCombo(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	LoadTexture(pDevice, ADRESS_TEXTURE_NUMBER_COMBO, &comboParts[NUMBER_COMBO]);
	LoadTexture(pDevice, ADRESS_TEXTURE_TEXT_COMBO,	&comboParts[TEXT_COMBO]);
	LoadTexture(pDevice, ADRESS_TEXTURE_BACKGROUND_COMBO, &comboParts[BACKGROUND_COMBO]);

	for (int i = 0; i < COMBOPARTS_MAX; i++)
	{
		InitialTexture(&comboParts[i]);
		MakeVertexObject(&comboParts[i]);
		comboParts[i].rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}

	comboParts[NUMBER_COMBO].position	  = POSITION_NUMBER_COMBO;
	comboParts[TEXT_COMBO].position		  = POSITION_TEXT_COMBO;
	comboParts[BACKGROUND_COMBO].position = POSITION_BACKGROUND_COMBO;

	comboParts[NUMBER_COMBO].size		= SIZE_NUMBER_COMBO;
	comboParts[TEXT_COMBO].size			= SIZE_TEXT_COMBO;
	comboParts[BACKGROUND_COMBO].size	= SIZE_BACKGROUND_COMBO;

	SetColorObject(&comboParts[NUMBER_COMBO],	 SET_COLOR_NOT_COLORED);
	SetColorObject(&comboParts[TEXT_COMBO],		 SET_COLOR_NOT_COLORED);
	SetColorObject(&comboParts[BACKGROUND_COMBO],SET_COLOR_NOT_COLORED);

	// ��]�I�u�W�F�N�g�p�̃T�[�N�����쐬
	CreateObjectCircle(&comboParts[BACKGROUND_COMBO], comboParts[BACKGROUND_COMBO].size.x, comboParts[BACKGROUND_COMBO].size.y);

	// �ő�l�ݒ�
	for (int nCntPlace = 0; nCntPlace < PLACE_MAX; nCntPlace++)
	{
		g_combo_max += (BASE_NUMBER -1)* (int)powf(BASE_NUMBER, (float)nCntPlace);
	}

	g_combo = 0;
	radian = 0;
	volumeUpEffectUsed = false;

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitCombo(void)
{
	for (int i = 0; i < COMBOPARTS_MAX; i++)
	{
		ReleaseTexture(&comboParts[i]);
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateCombo(void)
{
	// �R���{�w�i��]
	comboParts[BACKGROUND_COMBO].rotation.z += ROTATION_SPEED_COMBO_BACKGROUND;

	// �����̐F�X�V
	UpdateNumberColor();

	// �c�ɐL�т�G�t�F�N�g
	VolumeUpEffect();

	// �����ӂ�h�~
	if (g_combo < 0)
	{
		g_combo = 0;
	}
	if (g_combo >= g_combo_max)
	{
		g_combo = g_combo_max;
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawCombo(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	 //�w�i���ɕ`��
	DrawObject(pDevice, comboParts[BACKGROUND_COMBO]);
	SetVertexRotateObject(&comboParts[BACKGROUND_COMBO]);

	for (int nCntPlace = 0; nCntPlace < PLACE_MAX; nCntPlace++)
	{
		int number;

		number = g_combo % (int)(powf(BASE_NUMBER, (float)(PLACE_MAX - nCntPlace))) 
			/ (int)(powf(BASE_NUMBER, (float)(PLACE_MAX - nCntPlace - 1)));

		DrawObject(pDevice, comboParts[NUMBER_COMBO]);
		SetVertexCounter(&comboParts[NUMBER_COMBO], nCntPlace, INTERVAL_NUMBER);
		SetTextureCounter(&comboParts[NUMBER_COMBO], number, INTERVAL_NUMBER_TEXTURE);
	}

	DrawObject(pDevice, comboParts[TEXT_COMBO]);
	SetVertexObject(&comboParts[TEXT_COMBO]);
}

//=============================================================================
// �����{�����[���A�b�v�G�t�F�N�g����
//=============================================================================
void VolumeUpEffect(void)
{
	if (volumeUpEffectUsed == true)
	{
		comboParts[NUMBER_COMBO].size.y = SIZE_NUMBER_COMBO.y + VOLUME_ZOOM * sinf(radian);

		if (radian >= D3DX_PI)
		{
			radian = 0.0f;
			volumeUpEffectUsed = false;
		}

		radian += SPEED_VOLUMEUP_NUMBER;
	}
}

//=============================================================================
// �����J���[�X�V����
//=============================================================================
void UpdateNumberColor(void)
{
	int firstColorStartCombo  = 0;
	int secondColorStartCombo = 5;
	int thirdColorStartCombo  = 10;

	if (g_combo >= firstColorStartCombo && g_combo < secondColorStartCombo)
	{
		SetColorObject(&comboParts[NUMBER_COMBO], SET_COLOR_NOT_COLORED);
	}
	if (g_combo >= secondColorStartCombo && g_combo < thirdColorStartCombo)
	{
		SetColorObject(&comboParts[NUMBER_COMBO], SET_COLOR_YELLOW);
	}
	if (g_combo >= thirdColorStartCombo)
	{
		SetColorObject(&comboParts[NUMBER_COMBO], SET_COLOR_RED);
	}
}

//=============================================================================
// �R���{�̉��Z�i�����Ŏ󂯎�����l���R���{�ɉ��Z����j
//=============================================================================
void AddCombo(int value)
{
	g_combo += value;

	// �R���{�����Z���ꂽ��s������
	if (value > 0)
	{
		// �G�t�F�N�g�L����
		volumeUpEffectUsed = true;
	}
}

//=============================================================================
// �R���{�̑���i�����Ŏ󂯎�����l���R���{�ɑ������j
//=============================================================================
void SetCombo(int value)
{
	g_combo = value;
}
