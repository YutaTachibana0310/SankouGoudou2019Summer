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
// グローバル変数宣言
//*****************************************************************************
int	g_score;		// スコア
int	g_score_max;			
static float radian;
static bool	volumeUpEffectUsed;

//=============================================================================
// 初期化処理
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

	// 最大値設定
	for (int nCntPlace = 0; nCntPlace < PLACE_MAX; nCntPlace++)
	{
		g_score_max += (BASE_NUMBER -1)* (int)powf(BASE_NUMBER, (float)nCntPlace);
	}

	g_score = 0;
	radian = 0;
	volumeUpEffectUsed = false;
}

//=============================================================================
// 終了処理
//=============================================================================
void Score::Uninit(void)
{
	ReleaseTexture();
}

//=============================================================================
// 更新処理
//=============================================================================
void Score::Update(void)
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
// 数字ボリュームアップエフェクト処理
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
// スコアの加算（引数で受け取った値をスコアに加算する）
//=============================================================================
void Score::AddScore(int value)
{
	g_score += value;

	// スコアが加算されたら行う処理
	if (value > 0)
	{
		// エフェクト有効化
		volumeUpEffectUsed = true;
	}
}

int Score::SetScore() {
	return g_score;
}
