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

//=============================================================================
// ����������
//=============================================================================
void Combo::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	comboNumber->LoadTexture(pDevice, ADRESS_TEXTURE_NUMBER_COMBO);
	comboText->LoadTexture(pDevice, ADRESS_TEXTURE_TEXT_COMBO);
	comboBG->LoadTexture(pDevice, ADRESS_TEXTURE_BACKGROUND_COMBO);

	comboNumber->InitialTexture();
	comboText->InitialTexture();
	comboBG->InitialTexture();

	comboNumber->MakeVertexObject();
	comboText->MakeVertexObject();
	comboBG->MakeVertexObject();

	comboNumber->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	comboText->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	comboBG->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	comboNumber->position	  = POSITION_NUMBER_COMBO;
	comboText->position		  = POSITION_TEXT_COMBO;
	comboBG->position = POSITION_BACKGROUND_COMBO;

	comboNumber->size		= SIZE_NUMBER_COMBO;
	comboText->size			= SIZE_TEXT_COMBO;
	comboBG->size	= SIZE_BACKGROUND_COMBO;

	comboNumber->SetColorObject(SET_COLOR_NOT_COLORED);
	comboText->SetColorObject(SET_COLOR_NOT_COLORED);
	comboBG->SetColorObject(SET_COLOR_NOT_COLORED);

	// ��]�I�u�W�F�N�g�p�̃T�[�N�����쐬
	comboBG->CreateObjectCircle();

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
	comboNumber->ReleaseTexture();
	comboText->ReleaseTexture();
	comboBG->ReleaseTexture();
}

//=============================================================================
// �X�V����
//=============================================================================
void Combo::Update(void)
{
	// �R���{�w�i��]
	comboBG->rotation.z += ROTATION_SPEED_COMBO_BACKGROUND;

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
	comboBG->DrawObject(pDevice);
	comboBG->SetVertexRotateObject();

	for (int nCntPlace = 0; nCntPlace < PLACE_MAX; nCntPlace++)
	{
		int number;

		number = combo % (int)(powf(BASE_NUMBER, (float)(PLACE_MAX - nCntPlace))) 
			/ (int)(powf(BASE_NUMBER, (float)(PLACE_MAX - nCntPlace - 1)));

		comboNumber->DrawObject(pDevice);
		comboNumber->SetVertexCounter(nCntPlace, INTERVAL_NUMBER);
		comboNumber->SetTextureCounter(number, INTERVAL_NUMBER_TEXTURE);
	}	

	comboText->DrawObject(pDevice);
	comboText->SetVertexObject();
}

//=============================================================================
// �����{�����[���A�b�v�G�t�F�N�g����
//=============================================================================
void Combo::VolumeUpEffect(void)
{
	if (volumeUpEffectUsed == true)
	{
		comboNumber->size.y = SIZE_NUMBER_COMBO.y + VOLUME_ZOOM * sinf(radian);

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
		comboNumber->SetColorObject(SET_COLOR_NOT_COLORED);
	}
	if (combo >= secondColorStartCombo && combo < thirdColorStartCombo)
	{
		comboNumber->SetColorObject(SET_COLOR_YELLOW);
	}
	if (combo >= thirdColorStartCombo)
	{
		comboNumber->SetColorObject(SET_COLOR_RED);
	}
}
