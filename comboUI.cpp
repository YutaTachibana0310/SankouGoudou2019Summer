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
#define SPEED_VOLUMEUP_NUMBER_COMBO (0.2f)

// �T�C�Y��`
#define SIZE_NUMBER_COMBO		(D3DXVECTOR3(40.0f,75.0f,0.0f))
#define SIZE_TEXT_COMBO			(D3DXVECTOR3(45.0f,20.0f,0.0f))
#define SIZE_BACKGROUND_COMBO	(D3DXVECTOR3(200.0f,200.0f,0.0f))

// ���W��`
#define POSITION_NUMBER_COMBO		(D3DXVECTOR3(SCREEN_WIDTH / 10*2.0f, SCREEN_HEIGHT / 10*2.0f , 0.0f))
#define POSITION_TEXT_COMBO			(D3DXVECTOR3(SCREEN_WIDTH / 10*3.2f, SCREEN_HEIGHT / 10*2.3f , 0.0f))
#define POSITION_BACKGROUND_COMBO	(D3DXVECTOR3(SCREEN_WIDTH / 10*2.25f, SCREEN_HEIGHT / 10*2.0f , 0.0f))

//*****************************************************************************
// �R���X�g���N�^
//*****************************************************************************
Combo::Combo()
{
	number = new CounterObject();
	text = new Object();
	bg = new RotateObject();

	number->LoadTexture("data/TEXTURE/UI/number.png");
	text->LoadTexture("data/TEXTURE/UI/combo/comboText.png");
	bg->LoadTexture("data/TEXTURE/UI/combo/circleCombo.png");

	number->MakeVertex();
	text->MakeVertex();
	bg->MakeVertex();

	number->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	text->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	bg->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	number->position = POSITION_NUMBER_COMBO;
	text->position = POSITION_TEXT_COMBO;
	bg->position = POSITION_BACKGROUND_COMBO;

	number->size = SIZE_NUMBER_COMBO;
	text->size = SIZE_TEXT_COMBO;
	bg->size = SIZE_BACKGROUND_COMBO;

	number->SetColorObject(SET_COLOR_NOT_COLORED);
	text->SetColorObject(SET_COLOR_NOT_COLORED);
	bg->SetColorObject(SET_COLOR_NOT_COLORED);

	// ��]�I�u�W�F�N�g�p�̃T�[�N�����쐬
	bg->CreateObjectCircle();

	// �ő�l�ݒ�
	for (int nCntPlace = 0; nCntPlace < PLACE_MAX; nCntPlace++)
	{
		comboMax += (BASE_NUMBER - 1)* (int)powf(BASE_NUMBER, (float)nCntPlace);
	}

	combo = 0;
	radian = 0;
	volumeUpEffectUsed = false;
}

//*****************************************************************************
// �f�X�g���N�^
//*****************************************************************************
Combo::~Combo()
{
	delete number;
	number = NULL;

	delete text;
	text = NULL;

	delete bg;
	bg = NULL;
}

//=============================================================================
// �X�V����
//=============================================================================
void Combo::Update(void)
{
	// �R���{�w�i��]
	bg->rotation.z += ROTATION_SPEED_COMBO_BACKGROUND;

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
	 //�w�i���ɕ`��
	bg->Draw();
	bg->SetVertex();

	for (int nCntPlace = 0; nCntPlace < PLACE_MAX; nCntPlace++)
	{
		int num;

		num = combo % (int)(powf(BASE_NUMBER, (float)(PLACE_MAX - nCntPlace))) 
			/ (int)(powf(BASE_NUMBER, (float)(PLACE_MAX - nCntPlace - 1)));

		number->Draw();
		number->SetVertex(nCntPlace, INTERVAL_NUMBER);
		number->SetTexture(num, INTERVAL_NUMBER_TEXTURE);
	}	

	text->Draw();
	text->SetVertex();
}

//=============================================================================
// �����{�����[���A�b�v�G�t�F�N�g����
//=============================================================================
void Combo::VolumeUpEffect(void)
{
	if (volumeUpEffectUsed == true)
	{
		number->size.y = SIZE_NUMBER_COMBO.y + VOLUME_ZOOM * sinf(radian);

		if (radian >= D3DX_PI)
		{
			radian = 0.0f;
			volumeUpEffectUsed = false;
		}

		radian += SPEED_VOLUMEUP_NUMBER_COMBO;
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
		number->SetColorObject(SET_COLOR_NOT_COLORED);
	}
	if (combo >= secondColorStartCombo && combo < thirdColorStartCombo)
	{
		number->SetColorObject(SET_COLOR_YELLOW);
	}
	if (combo >= thirdColorStartCombo)
	{
		number->SetColorObject(SET_COLOR_RED);
	}
}
