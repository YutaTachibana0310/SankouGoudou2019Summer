//=============================================================================
//
// �X�R�A���� [score.cpp]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#include "score.h"
#include "UIdrawer.h"
#include "input.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	INTERVAL_NUMBER	(40.0f)	// �X�R�A�����̕\���Ԋu
#define	PLACE_MAX		(4)		// �X�R�A�̌���
#define SIZE_X_SCORE	(20)
#define SIZE_Y_SCORE	(30)
#define VOLUME_ZOOM		(50.0f)
#define POSITION_SCORE	(D3DXVECTOR3(SCREEN_WIDTH / 10 * 8.5, SCREEN_HEIGHT / 10 * 1, 0.0f))
#define BASE_NUMBER		(10.0f) // �i��

//*****************************************************************************
// �O���[�o���ϐ��錾
//*****************************************************************************
OBJECT	score;					
int		g_score		= 0; // �X�R�A
int		g_score_max = 0;			

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
	score.size	   = D3DXVECTOR3(SIZE_X_SCORE, SIZE_Y_SCORE, 0.0f);

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
		SetTextureCounter(&score, number);
	}
}

//=============================================================================
// �X�R�A�̕ύX
//=============================================================================
void ChangeScore(int value)
{
	g_score += value;

	if (g_score < 0)
	{
		g_score = 0;
	}
	else if (g_score >= (int)(powf(BASE_NUMBER, (float)(PLACE_MAX + 1))))
	{
		g_score = (int)(powf(BASE_NUMBER, (float)(PLACE_MAX + 1))) - 1;
	}

	// �����ӂ�h�~
	if (g_score >= g_score_max)
	{
		g_score = g_score_max;
	}
}
