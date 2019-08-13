//=============================================================================
//
// コンボ処理 [combo.cpp]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#include "main.h"
#include "comboUI.h"
#include "UIdrawer.h"
#include "input.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define COMBOPARTS_MAX		(3)
#define	INTERVAL_NUMBER		(80.0f)			// コンボ数字の表示間隔
#define	INTERVAL_NUMBER_TEXTURE	(0.097f)	// テクスチャ内コンボ数字の表示間隔
#define	PLACE_MAX			(2)				// コンボの桁数
#define BASE_NUMBER			(10)			// 進数
#define VOLUME_ZOOM			(50.0f)
#define ROTATION_SPEED_COMBO_BACKGROUND (0.01f)

// サイズ定義
#define SIZE_NUMBER_COMBO		(D3DXVECTOR3(40.0f,75.0f,0.0f))
#define SIZE_TEXT_COMBO			(D3DXVECTOR3(45.0f,20.0f,0.0f))
#define SIZE_BACKGROUND_COMBO	(D3DXVECTOR3(200.0f,200.0f,0.0f))

// 座標定義
#define POSITION_NUMBER_COMBO		(D3DXVECTOR3(SCREEN_WIDTH / 10*2.0f, SCREEN_HEIGHT / 10*2.0f , 0.0f))
#define POSITION_TEXT_COMBO			(D3DXVECTOR3(SCREEN_WIDTH / 10*3.2f, SCREEN_HEIGHT / 10*2.3f , 0.0f))
#define POSITION_BACKGROUND_COMBO	(D3DXVECTOR3(SCREEN_WIDTH / 10*2.25f, SCREEN_HEIGHT / 10*2.0f , 0.0f))

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
static void VolumeUpEffect(void);
void UpdateNumberColor(void);

//*****************************************************************************
// グローバル変数宣言
//*****************************************************************************
OBJECT	comboParts[COMBOPARTS_MAX];
int		g_combo;	// コンボ
int		g_combo_max;
static float radian;
static bool	volumeUpEffectUsed;

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitCombo(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	LoadTexture(pDevice, ADRESS_TEXTURE_NUMBER_COMBO, &comboParts[NUMBER_COMBO]);
	LoadTexture(pDevice, ADRESS_TEXTURE_TEXT_COMBO,	&comboParts[TEXT_COMBO]);
	LoadTexture(pDevice, ADRESS_TEXTURE_BACKGROUND_COMBO, &comboParts[BACKGROUND_COMBO]);

	for (int i = 0; i < COMBOPARTS_MAX; i++)
	{
		InitialTexture(&comboParts[i]);
		MakeVertexObject(&comboParts[i]);
		comboParts[i].rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}

	comboParts[NUMBER_COMBO].position	  = POSITION_NUMBER_COMBO;
	comboParts[TEXT_COMBO].position		  = POSITION_TEXT_COMBO;
	comboParts[BACKGROUND_COMBO].position = POSITION_BACKGROUND_COMBO;

	comboParts[NUMBER_COMBO].size		= SIZE_NUMBER_COMBO;
	comboParts[TEXT_COMBO].size			= SIZE_TEXT_COMBO;
	comboParts[BACKGROUND_COMBO].size	= SIZE_BACKGROUND_COMBO;

	SetColorObject(&comboParts[NUMBER_COMBO],	 SET_COLOR_NOT_COLORED);
	SetColorObject(&comboParts[TEXT_COMBO],		 SET_COLOR_NOT_COLORED);
	SetColorObject(&comboParts[BACKGROUND_COMBO],SET_COLOR_NOT_COLORED);

	// 回転オブジェクト用のサークルを作成
	CreateObjectCircle(&comboParts[BACKGROUND_COMBO], comboParts[BACKGROUND_COMBO].size.x, comboParts[BACKGROUND_COMBO].size.y);

	// 最大値設定
	for (int nCntPlace = 0; nCntPlace < PLACE_MAX; nCntPlace++)
	{
		g_combo_max += (BASE_NUMBER -1)* (int)powf(BASE_NUMBER, (float)nCntPlace);
	}

	g_combo = 0;
	radian = 0;
	volumeUpEffectUsed = false;

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitCombo(void)
{
	for (int i = 0; i < COMBOPARTS_MAX; i++)
	{
		ReleaseTexture(&comboParts[i]);
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateCombo(void)
{
	// コンボ背景回転
	comboParts[BACKGROUND_COMBO].rotation.z += ROTATION_SPEED_COMBO_BACKGROUND;

	// 数字の色更新
	UpdateNumberColor();

	// 縦に伸びるエフェクト
	VolumeUpEffect();

	// 桁あふれ防止
	if (g_combo < 0)
	{
		g_combo = 0;
	}
	if (g_combo >= g_combo_max)
	{
		g_combo = g_combo_max;
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawCombo(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	 //背景を先に描画
	DrawObject(pDevice, comboParts[BACKGROUND_COMBO]);
	SetVertexRotateObject(&comboParts[BACKGROUND_COMBO]);

	for (int nCntPlace = 0; nCntPlace < PLACE_MAX; nCntPlace++)
	{
		int number;

		number = g_combo % (int)(powf(BASE_NUMBER, (float)(PLACE_MAX - nCntPlace))) 
			/ (int)(powf(BASE_NUMBER, (float)(PLACE_MAX - nCntPlace - 1)));

		DrawObject(pDevice, comboParts[NUMBER_COMBO]);
		SetVertexCounter(&comboParts[NUMBER_COMBO], nCntPlace, INTERVAL_NUMBER);
		SetTextureCounter(&comboParts[NUMBER_COMBO], number, INTERVAL_NUMBER_TEXTURE);
	}

	DrawObject(pDevice, comboParts[TEXT_COMBO]);
	SetVertexObject(&comboParts[TEXT_COMBO]);
}

//=============================================================================
// 数字ボリュームアップエフェクト処理
//=============================================================================
void VolumeUpEffect(void)
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
// 数字カラー更新処理
//=============================================================================
void UpdateNumberColor(void)
{
	int firstColorStartCombo  = 0;
	int secondColorStartCombo = 5;
	int thirdColorStartCombo  = 10;

	if (g_combo >= firstColorStartCombo && g_combo < secondColorStartCombo)
	{
		SetColorObject(&comboParts[NUMBER_COMBO], SET_COLOR_NOT_COLORED);
	}
	if (g_combo >= secondColorStartCombo && g_combo < thirdColorStartCombo)
	{
		SetColorObject(&comboParts[NUMBER_COMBO], SET_COLOR_YELLOW);
	}
	if (g_combo >= thirdColorStartCombo)
	{
		SetColorObject(&comboParts[NUMBER_COMBO], SET_COLOR_RED);
	}
}

//=============================================================================
// コンボの加算（引数で受け取った値をコンボに加算する）
//=============================================================================
void AddCombo(int value)
{
	g_combo += value;

	// コンボが加算されたら行う処理
	if (value > 0)
	{
		// エフェクト有効化
		volumeUpEffectUsed = true;
	}
}

//=============================================================================
// コンボの代入（引数で受け取った値をコンボに代入する）
//=============================================================================
void SetCombo(int value)
{
	g_combo = value;
}
