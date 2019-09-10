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
#include "Viewer3D.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	INTERVAL_NUMBER		(120.0f)	// �R���{�����̕\���Ԋu
#define	INTERVAL_NUMBER_TEXTURE	(0.1f)	// �e�N�X�`�����R���{�����̕\���Ԋu
#define	PLACE_MAX			(3)			// �R���{�̌���
#define BASE_NUMBER			(10)		// �i��
#define VOLUME_ZOOM			(50.0f)
#define SPEED_VOLUMEUP_NUMBER_COMBO (0.2f)

// �T�C�Y��`
#define SIZE_NUMBER_COMBO		(D3DXVECTOR3(120.0f,200.0f,0.0f))
#define SIZE_BACKGROUND_COMBO	(D3DXVECTOR3(512.0f,256.0f,0.0f))

// ���W��`(3D)
#define POSITION_NUMBER_COMBO	(D3DXVECTOR3(160.0f,200.0f,0.0f))
#define POSITION_BG_COMBO		(D3DXVECTOR3(512.0f,256.0f,0.0f))

//*****************************************************************************
// �R���X�g���N�^
//*****************************************************************************
Combo::Combo()
{
	//�i���o�[
	number = new CounterObject();
	number->LoadTexture("data/TEXTURE/UI/Combo/number_L.png");
	number->MakeVertex();
	number->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	number->position = POSITION_NUMBER_COMBO/2;
	number->size = SIZE_NUMBER_COMBO/2;
	number->SetColorObject(SET_COLOR_NOT_COLORED);

	//�w�i
	bg = new RotateObject();
	bg->LoadTexture("data/TEXTURE/UI/Combo/comboBG.png");
	bg->MakeVertex();
	bg->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	bg->CreateObjectCircle();
	bg->position = POSITION_BG_COMBO/2;
	bg->size = SIZE_BACKGROUND_COMBO/2;
	bg->SetColorObject(SET_COLOR_NOT_COLORED);
	bg->CreateObjectCircle();

	//�r���A�[
	viewer = new Viewer3D(SIZE_BACKGROUND_COMBO.x, SIZE_BACKGROUND_COMBO.y, D3DXVECTOR2(20.0f, 10.0f));
	viewer->SetPosition(D3DXVECTOR3((float)-SCREEN_WIDTH / 15.5f,  (float)SCREEN_HEIGHT/23.0f, 0.0f));
	viewer->SetRotation(0.0f, -30.0f, 0.0f);

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
	SAFE_DELETE(number);
	SAFE_DELETE(bg);
	SAFE_DELETE(viewer);
}

//=============================================================================
// �X�V����
//=============================================================================
void Combo::Update(void)
{
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
	viewer->Begin2D();

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

	viewer->End2D();
	viewer->Draw3D();
}

//=============================================================================
// �����{�����[���A�b�v�G�t�F�N�g����
//=============================================================================
void Combo::VolumeUpEffect(void)
{
	if (volumeUpEffectUsed == true)
	{
		number->size.y = SIZE_NUMBER_COMBO.y/2 + VOLUME_ZOOM * sinf(radian);

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
	int secondColorStartCombo = 50;
	int thirdColorStartCombo  = 100;

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
