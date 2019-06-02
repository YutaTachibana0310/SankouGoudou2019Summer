//=============================================================================
//
// �R���{���� [combo.cpp]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#include "main.h"
#include "combo.h"
#include "UIdrawer.h"
#include "input.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define COMBOPARTS_MAX (2)
#define	INTERVAL_NUMBER	(80.0f)	// �R���{�����̕\���Ԋu
#define	PLACE_MAX	(2)			// �R���{�̌���
#define SIZE_X_NUMBER_COMBO (40)
#define SIZE_X_TEXT_COMBO (130)
#define SIZE_Y_NUMBER_COMBO (75)
#define SIZE_Y_TEXT_COMBO (75)
#define VOLUME_ZOOM (50.0f)
#define POSITION_NUMBER_COMBO (D3DXVECTOR3(SCREEN_WIDTH / 10*2.2, SCREEN_HEIGHT / 10 , 0.0f))
#define POSITION_TEXT_COMBO (D3DXVECTOR3(SCREEN_WIDTH / 10, SCREEN_HEIGHT / 10 , 0.0f))

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void VolumeUpEffect(void);

//*****************************************************************************
// �O���[�o���ϐ��錾
//*****************************************************************************
OBJECT comboParts[COMBOPARTS_MAX];
int	g_combo = 0;	// �R���{
int g_combo_max = 0;			
float radian = 0;
bool volumeUpEffectUse = false;

//=============================================================================
// ����������
//=============================================================================
HRESULT InitCombo(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	LoadTexture(pDevice, ADRESS_TEXTURE_NUMBER_COMBO, &comboParts[NUMBER_COMBO]);
	LoadTexture(pDevice, ADRESS_TEXTURE_TEXT_COMBO, &comboParts[TEXT_COMBO]);

	for (int i = 0; i < COMBOPARTS_MAX; i++)
	{
		InitialTexture(&comboParts[i]);
		MakeVertexObject(&comboParts[i]);
		comboParts[i].rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}

	comboParts[NUMBER_COMBO].position = POSITION_NUMBER_COMBO;
	comboParts[TEXT_COMBO].position = POSITION_TEXT_COMBO;
	comboParts[NUMBER_COMBO].size = D3DXVECTOR3(SIZE_X_NUMBER_COMBO, SIZE_Y_NUMBER_COMBO, 0.0f);
	comboParts[TEXT_COMBO].size = D3DXVECTOR3(SIZE_X_TEXT_COMBO, SIZE_Y_TEXT_COMBO, 0.0f);

	SetColorObject(&comboParts[NUMBER_COMBO], SET_COLOR_NOT_COLORED);
	SetColorObject(&comboParts[TEXT_COMBO], SET_COLOR_NOT_COLORED);

	// �ő�l�ݒ�
	for (int nCntPlace = 0; nCntPlace < PLACE_MAX; nCntPlace++)
	{
		g_combo_max += 9 * (int)powf(10.0f, (float)nCntPlace);
	}

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
	VolumeUpEffect();
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawCombo(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int nCntPlace = 0; nCntPlace < PLACE_MAX; nCntPlace++)
	{
		int number;

		number = g_combo % (int)(powf(10.0f, (float)(PLACE_MAX - nCntPlace))) / (int)(powf(10.0f, (float)(PLACE_MAX - nCntPlace - 1)));

		DrawObject(pDevice, comboParts[NUMBER_COMBO]);

		// ���_���W�̐ݒ�
		SetVertexCounter(&comboParts[NUMBER_COMBO], nCntPlace, INTERVAL_NUMBER);

		// �e�N�X�`�����W�̐ݒ�
		SetTextureCounter(&comboParts[NUMBER_COMBO], number);
	}

	DrawObject(pDevice, comboParts[TEXT_COMBO]);
	SetVertexObject(&comboParts[TEXT_COMBO]);
}

//=============================================================================
// �R���{�̕ύX
//=============================================================================
void ChangeCombo(int value)
{
	g_combo += value;

	if (g_combo < 0)
	{
		g_combo = 0;
	}
	else if (g_combo >= (int)(powf(10.0f, (float)(PLACE_MAX + 1))))
	{
		g_combo = (int)(powf(10.0f, (float)(PLACE_MAX + 1))) - 1;
	}

	// �����ӂ�h�~
	if (g_combo >= g_combo_max)
	{
		g_combo = g_combo_max;
	}

	// �G�t�F�N�g�L����
	volumeUpEffectUse = true;
}

//=============================================================================
// �����{�����[���A�b�v�G�t�F�N�g����
//=============================================================================
void VolumeUpEffect(void)
{
	if (volumeUpEffectUse == true)
	{
		comboParts[NUMBER_COMBO].size.y = SIZE_Y_NUMBER_COMBO + VOLUME_ZOOM * sinf(radian);

		if (radian >= D3DX_PI)
		{
			radian = 0.0f;
			volumeUpEffectUse = false;
		}

		radian += 0.20f;
	}
}
