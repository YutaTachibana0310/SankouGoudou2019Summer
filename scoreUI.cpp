//=============================================================================
//
// �X�R�A���� [score.cpp]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#include "scoreUI.h"
#include "UIdrawer.h"
#include "input.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define SPEED_VOLUMEUP_NUMBER_SCORE (0.2f)

//*****************************************************************************
// �R���X�g���N�^
//*****************************************************************************
Score::Score()
{
	//�J�E���^�[
	counter = new CounterObject();
	counter->LoadTexture("data/TEXTURE/UI/Score/number_L.png");
	counter->MakeVertex();

	counter->position = POSITION_NUMBER_SCORE;
	counter->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	counter->size = SIZE_NUMBER_SCORE;

	counter->SetColorObject(SET_COLOR_NOT_COLORED);

	//�w�i
	bg = new CounterObject();
	bg->LoadTexture("data/TEXTURE/UI/Score/scoreBG.png");
	bg->MakeVertex();

	bg->position = POSITION_BG_SCORE;
	bg->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	bg->size = SIZE_BG_SCORE;

	bg->SetColorObject(SET_COLOR_NOT_COLORED);

	// �ő�l�ݒ�
	for (int nCntPlace = 0; nCntPlace < PLACE_MAX; nCntPlace++)
	{
		score_max += (BASE_NUMBER - 1)* (int)powf(BASE_NUMBER, (float)nCntPlace);
	}

	score = 0;
	radian = 0;
	volumeUpEffectUsed = false;
}

//*****************************************************************************
// �f�X�g���N�^
//*****************************************************************************
Score::~Score()
{
	delete counter;
	counter = NULL;

	delete bg;
	bg = NULL;
}

//=============================================================================
// �X�V����
//=============================================================================
void Score::Update(void)
{
	VolumeUpEffect();

	// �����ӂ�h�~
	if (score < 0)
	{
		score = 0;
	}
	if (score >= score_max)
	{
		score = score_max;
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void Score::Draw(void)
{
	bg->Draw();
	bg->SetVertex();

	for (int nCntPlace = 0; nCntPlace < PLACE_MAX; nCntPlace++)
	{
		int scoreber;

		scoreber = score % (int)(powf(BASE_NUMBER, (float)(PLACE_MAX - nCntPlace))) / (int)(powf(BASE_NUMBER, (float)(PLACE_MAX - nCntPlace - 1)));

		counter->Draw();
		counter->SetVertex(nCntPlace, INTERVAL_NUMBER);
		counter->SetTexture(scoreber, INTERVAL_NUMBER_TEXTURE);
	}	
}

//=============================================================================
// �����{�����[���A�b�v�G�t�F�N�g����
//=============================================================================
void Score::VolumeUpEffect(void)
{
	if (volumeUpEffectUsed == true)
	{
		counter->size.y = SIZE_NUMBER_SCORE.y + VOLUME_ZOOM * sinf(radian);

		if (radian >= D3DX_PI)
		{
			radian = 0.0f;
			volumeUpEffectUsed = false;
		}

		radian += SPEED_VOLUMEUP_NUMBER_SCORE;
	}
}
