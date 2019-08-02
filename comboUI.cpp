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
// �O���[�o���ϐ��錾
//*****************************************************************************
Object comboParts[COMBOPARTS_MAX];

//=============================================================================
// ����������
//=============================================================================
void Combo::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	object->LoadTexture(pDevice, ADRESS_TEXTURE_NUMBER_COMBO, &comboParts[NUMBER_COMBO]);
	object->LoadTexture(pDevice, ADRESS_TEXTURE_TEXT_COMBO,	&comboParts[TEXT_COMBO]);
	object->LoadTexture(pDevice, ADRESS_TEXTURE_BACKGROUND_COMBO, &comboParts[BACKGROUND_COMBO]);

	for (int i = 0; i < COMBOPARTS_MAX; i++)
	{
		object->InitialTexture(&comboParts[i]);
		object->MakeVertexObject(&comboParts[i]);
		comboParts[i].rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}

	comboParts[NUMBER_COMBO].position	  = POSITION_NUMBER_COMBO;
	comboParts[TEXT_COMBO].position		  = POSITION_TEXT_COMBO;
	comboParts[BACKGROUND_COMBO].position = POSITION_BACKGROUND_COMBO;

	comboParts[NUMBER_COMBO].size		= SIZE_NUMBER_COMBO;
	comboParts[TEXT_COMBO].size			= SIZE_TEXT_COMBO;
	comboParts[BACKGROUND_COMBO].size	= SIZE_BACKGROUND_COMBO;

	object->SetColorObject(&comboParts[NUMBER_COMBO],	 SET_COLOR_NOT_COLORED);
	object->SetColorObject(&comboParts[TEXT_COMBO],		 SET_COLOR_NOT_COLORED);
	object->SetColorObject(&comboParts[BACKGROUND_COMBO],SET_COLOR_NOT_COLORED);

	// ��]�I�u�W�F�N�g�p�̃T�[�N�����쐬
	object->CreateObjectCircle(&comboParts[BACKGROUND_COMBO], comboParts[BACKGROUND_COMBO].size.x, comboParts[BACKGROUND_COMBO].size.y);

	// �ő�l�ݒ�
	for (int nCntPlace = 0; nCntPlace < PLACE_MAX; nCntPlace++)
	{
		comboMax += (BASE_NUMBER -1)* (int)powf(BASE_NUMBER, (float)nCntPlace);
	}

	combo = 0;
	radian = 0;
	volumeUpEffectUsed = false;
}

//=============================================================================
// �I������
//=============================================================================
void Combo::Uninit(void)
{
	for (int i = 0; i < COMBOPARTS_MAX; i++)
	{
		object->ReleaseTexture(&comboParts[i]);
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void Combo::Update(void)
{
	// �R���{�w�i��]
	comboParts[BACKGROUND_COMBO].rotation.z += ROTATION_SPEED_COMBO_BACKGROUND;

	// �����̐F�X�V
	UpdateNumberColor();

	// �c�ɐL�т�G�t�F�N�g
	VolumeUpEffect();

	// �����ӂ�h�~
	if (combo < 0)
	{
		combo = 0;
	}
	if (combo >= comboMax)
	{
		combo = comboMax;
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void Combo::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	 //�w�i���ɕ`��
	object->DrawObject(pDevice, &comboParts[BACKGROUND_COMBO]);
	object->SetVertexRotateObject(&comboParts[BACKGROUND_COMBO]);

	for (int nCntPlace = 0; nCntPlace < PLACE_MAX; nCntPlace++)
	{
		int number;

		number = combo % (int)(powf(BASE_NUMBER, (float)(PLACE_MAX - nCntPlace))) 
			/ (int)(powf(BASE_NUMBER, (float)(PLACE_MAX - nCntPlace - 1)));

		object->DrawObject(pDevice, &comboParts[NUMBER_COMBO]);
		object->SetVertexCounter(&comboParts[NUMBER_COMBO], nCntPlace, INTERVAL_NUMBER);
		object->SetTextureCounter(&comboParts[NUMBER_COMBO], number, INTERVAL_NUMBER_TEXTURE);
	}	

	object->DrawObject(pDevice, &comboParts[TEXT_COMBO]);
	object->SetVertexObject(&comboParts[TEXT_COMBO]);
}

//=============================================================================
// �����{�����[���A�b�v�G�t�F�N�g����
//=============================================================================
void Combo::VolumeUpEffect(void)
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
void Combo::UpdateNumberColor(void)
{
	int firstColorStartCombo  = 0;
	int secondColorStartCombo = 5;
	int thirdColorStartCombo  = 10;

	if (combo >= firstColorStartCombo && combo < secondColorStartCombo)
	{
		object->SetColorObject(&comboParts[NUMBER_COMBO], SET_COLOR_NOT_COLORED);
	}
	if (combo >= secondColorStartCombo && combo < thirdColorStartCombo)
	{
		object->SetColorObject(&comboParts[NUMBER_COMBO], SET_COLOR_YELLOW);
	}
	if (combo >= thirdColorStartCombo)
	{
		object->SetColorObject(&comboParts[NUMBER_COMBO], SET_COLOR_RED);
	}
}
