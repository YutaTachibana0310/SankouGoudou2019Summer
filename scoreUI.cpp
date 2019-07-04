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
// �}�N����`
//*****************************************************************************
#define	INTERVAL_NUMBER	(40.0f)				// �X�R�A�����̕\���Ԋu
#define	INTERVAL_NUMBER_TEXTURE	(0.097f)	// �e�N�X�`���e�N�X�`�����̃X�R�A�����̕\���Ԋu
#define	PLACE_MAX		(4)					// �X�R�A�̌���
#define BASE_NUMBER		(10)				// �i��
#define VOLUME_ZOOM		(30.0f)
#define SIZE_SCORE		(D3DXVECTOR3(20.0f,30.0f,0.0f))
#define POSITION_SCORE	(D3DXVECTOR3(SCREEN_WIDTH / 10 * 8.8f, SCREEN_HEIGHT / 10 * 8, 0.0f))

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
static void VolumeUpEffect(void);

//*****************************************************************************
// �O���[�o���ϐ��錾
//*****************************************************************************
OBJECT	score;					
int		g_score		= 0;		// �X�R�A
int		g_score_max = 0;			
static float radian = 0;
static bool	volumeUpEffectUsed = false;

//=============================================================================
// ����������
//=============================================================================
HRESULT InitScore(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	LoadTexture(pDevice, ADRESS_TEXTURE_SCORE, &score);
	InitialTexture(&score);
	MakeVertexObject(&score);

	score.position = POSITION_SCORE;
	score.rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	score.size	   = SIZE_SCORE;

	SetColorObject(&score, SET_COLOR_NOT_COLORED);

	// �ő�l�ݒ�
	for (int nCntPlace = 0; nCntPlace < PLACE_MAX; nCntPlace++)
	{
		g_score_max += (BASE_NUMBER -1)* (int)powf(BASE_NUMBER, (float)nCntPlace);
	}

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitScore(void)
{
	ReleaseTexture(&score);
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateScore(void)
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
void DrawScore(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int nCntPlace = 0; nCntPlace < PLACE_MAX; nCntPlace++)
	{
		int number;

		number = g_score % (int)(powf(BASE_NUMBER, (float)(PLACE_MAX - nCntPlace))) / (int)(powf(BASE_NUMBER, (float)(PLACE_MAX - nCntPlace - 1)));

		DrawObject(pDevice, score);
		SetVertexCounter(&score, nCntPlace, INTERVAL_NUMBER);
		SetTextureCounter(&score, number, INTERVAL_NUMBER_TEXTURE);
	}
}

//=============================================================================
// �����{�����[���A�b�v�G�t�F�N�g����
//=============================================================================
void VolumeUpEffect(void)
{
	if (volumeUpEffectUsed == true)
	{
		score.size.y = SIZE_SCORE.y + VOLUME_ZOOM * sinf(radian);

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
void AddScore(int value)
{
	g_score += value;

	// �X�R�A�����Z���ꂽ��s������
	if (value > 0)
	{
		// �G�t�F�N�g�L����
		volumeUpEffectUsed = true;
	}
}
