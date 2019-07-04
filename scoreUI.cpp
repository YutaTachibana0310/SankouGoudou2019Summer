//=============================================================================
//
// スコア処理 [score.cpp]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#include "scoreUI.h"
#include "UIdrawer.h"
#include "input.h"
#include "comboUI.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	INTERVAL_NUMBER	(40.0f)				// スコア数字の表示間隔
#define	INTERVAL_NUMBER_TEXTURE	(0.097f)	// テクスチャテクスチャ内のスコア数字の表示間隔
#define	PLACE_MAX		(4)					// スコアの桁数
#define BASE_NUMBER		(10)				// 進数
#define VOLUME_ZOOM		(30.0f)
#define SIZE_SCORE		(D3DXVECTOR3(20.0f,30.0f,0.0f))
#define POSITION_SCORE	(D3DXVECTOR3(SCREEN_WIDTH / 10 * 8.8f, SCREEN_HEIGHT / 10 * 8, 0.0f))

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
static void VolumeUpEffect(void);

//*****************************************************************************
// グローバル変数宣言
//*****************************************************************************
OBJECT	score;					
int		g_score		= 0;		// スコア
int		g_score_max = 0;			
static float radian = 0;
static bool	volumeUpEffectUsed = false;

//=============================================================================
// 初期化処理
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

	// 最大値設定
	for (int nCntPlace = 0; nCntPlace < PLACE_MAX; nCntPlace++)
	{
		g_score_max += (BASE_NUMBER -1)* (int)powf(BASE_NUMBER, (float)nCntPlace);
	}

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitScore(void)
{
	ReleaseTexture(&score);
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateScore(void)
{
	VolumeUpEffect();

	// 桁あふれ防止
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
// 描画処理
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
// 数字ボリュームアップエフェクト処理
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
// スコアの加算（引数で受け取った値をスコアに加算する）
//=============================================================================
void AddScore(int value)
{
	g_score += value;

	// スコアが加算されたら行う処理
	if (value > 0)
	{
		// エフェクト有効化
		volumeUpEffectUsed = true;
	}
}
