//=============================================================================
//
// �X�R�A���� [score.cpp]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#include "scoreUI.h"
#include "UIdrawer.h"
#include "input.h"
#include "comboUI.h"

//*****************************************************************************
// �O���[�o���ϐ��錾
//*****************************************************************************
int	g_score;		// �X�R�A
int	g_score_max;			
static float radian;
static bool	volumeUpEffectUsed;

//=============================================================================
// ����������
//=============================================================================
void Score::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	LoadTexture(pDevice, ADRESS_TEXTURE_SCORE);
	InitialTexture();
	MakeVertexObject();

	position = POSITION_SCORE;
	rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	size	    = SIZE_SCORE;

	SetColorObject(SET_COLOR_NOT_COLORED);

	// �ő�l�ݒ�
	for (int nCntPlace = 0; nCntPlace < PLACE_MAX; nCntPlace++)
	{
		g_score_max += (BASE_NUMBER -1)* (int)powf(BASE_NUMBER, (float)nCntPlace);
	}

	g_score = 0;
	radian = 0;
	volumeUpEffectUsed = false;
}

//=============================================================================
// �I������
//=============================================================================
void Score::Uninit(void)
{
	ReleaseTexture();
}

//=============================================================================
// �X�V����
//=============================================================================
void Score::Update(void)
{
	VolumeUpEffect();

	// �����ӂ�h�~
	if (g_score < 0)
	{
		g_score = 0;
	}
	if (g_score >= g_score_max)
	{
		g_score = g_score_max;
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void Score::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int nCntPlace = 0; nCntPlace < PLACE_MAX; nCntPlace++)
	{
		int number;

		number = g_score % (int)(powf(BASE_NUMBER, (float)(PLACE_MAX - nCntPlace))) / (int)(powf(BASE_NUMBER, (float)(PLACE_MAX - nCntPlace - 1)));

		object->DrawObject(pDevice);
		object->SetVertexCounter(nCntPlace, INTERVAL_NUMBER);
		object->SetTextureCounter(number, INTERVAL_NUMBER_TEXTURE);
	}	
}

//=============================================================================
// �����{�����[���A�b�v�G�t�F�N�g����
//=============================================================================
void Score::VolumeUpEffect(void)
{
	if (volumeUpEffectUsed == true)
	{
		size.y = SIZE_SCORE.y + VOLUME_ZOOM * sinf(radian);

		if (radian >= D3DX_PI)
		{
			radian = 0.0f;
			volumeUpEffectUsed = false;
		}

		radian += SPEED_VOLUMEUP_NUMBER;
	}
}

//=============================================================================
// �X�R�A�̉��Z�i�����Ŏ󂯎�����l���X�R�A�ɉ��Z����j
//=============================================================================
void Score::AddScore(int value)
{
	g_score += value;

	// �X�R�A�����Z���ꂽ��s������
	if (value > 0)
	{
		// �G�t�F�N�g�L����
		volumeUpEffectUsed = true;
	}
}

int Score::SetScore() {
	return g_score;
}
