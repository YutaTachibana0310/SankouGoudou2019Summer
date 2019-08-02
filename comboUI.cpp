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
// グローバル変数宣言
//*****************************************************************************
Object comboParts[COMBOPARTS_MAX];

//=============================================================================
// 初期化処理
//=============================================================================
void Combo::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	object->LoadTexture(pDevice, ADRESS_TEXTURE_NUMBER_COMBO, &comboParts[NUMBER_COMBO]);
	object->LoadTexture(pDevice, ADRESS_TEXTURE_TEXT_COMBO,	&comboParts[TEXT_COMBO]);
	object->LoadTexture(pDevice, ADRESS_TEXTURE_BACKGROUND_COMBO, &comboParts[BACKGROUND_COMBO]);

	for (int i = 0; i < COMBOPARTS_MAX; i++)
	{
		object->InitialTexture(&comboParts[i]);
		object->MakeVertexObject(&comboParts[i]);
		comboParts[i].rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}

	comboParts[NUMBER_COMBO].position	  = POSITION_NUMBER_COMBO;
	comboParts[TEXT_COMBO].position		  = POSITION_TEXT_COMBO;
	comboParts[BACKGROUND_COMBO].position = POSITION_BACKGROUND_COMBO;

	comboParts[NUMBER_COMBO].size		= SIZE_NUMBER_COMBO;
	comboParts[TEXT_COMBO].size			= SIZE_TEXT_COMBO;
	comboParts[BACKGROUND_COMBO].size	= SIZE_BACKGROUND_COMBO;

	object->SetColorObject(&comboParts[NUMBER_COMBO],	 SET_COLOR_NOT_COLORED);
	object->SetColorObject(&comboParts[TEXT_COMBO],		 SET_COLOR_NOT_COLORED);
	object->SetColorObject(&comboParts[BACKGROUND_COMBO],SET_COLOR_NOT_COLORED);

	// 回転オブジェクト用のサークルを作成
	object->CreateObjectCircle(&comboParts[BACKGROUND_COMBO], comboParts[BACKGROUND_COMBO].size.x, comboParts[BACKGROUND_COMBO].size.y);

	// 最大値設定
	for (int nCntPlace = 0; nCntPlace < PLACE_MAX; nCntPlace++)
	{
		comboMax += (BASE_NUMBER -1)* (int)powf(BASE_NUMBER, (float)nCntPlace);
	}

	combo = 0;
	radian = 0;
	volumeUpEffectUsed = false;
}

//=============================================================================
// 終了処理
//=============================================================================
void Combo::Uninit(void)
{
	for (int i = 0; i < COMBOPARTS_MAX; i++)
	{
		object->ReleaseTexture(&comboParts[i]);
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void Combo::Update(void)
{
	// コンボ背景回転
	comboParts[BACKGROUND_COMBO].rotation.z += ROTATION_SPEED_COMBO_BACKGROUND;

	// 数字の色更新
	UpdateNumberColor();

	// 縦に伸びるエフェクト
	VolumeUpEffect();

	// 桁あふれ防止
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
// 描画処理
//=============================================================================
void Combo::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	 //背景を先に描画
	object->DrawObject(pDevice, &comboParts[BACKGROUND_COMBO]);
	object->SetVertexRotateObject(&comboParts[BACKGROUND_COMBO]);

	for (int nCntPlace = 0; nCntPlace < PLACE_MAX; nCntPlace++)
	{
		int number;

		number = combo % (int)(powf(BASE_NUMBER, (float)(PLACE_MAX - nCntPlace))) 
			/ (int)(powf(BASE_NUMBER, (float)(PLACE_MAX - nCntPlace - 1)));

		object->DrawObject(pDevice, &comboParts[NUMBER_COMBO]);
		object->SetVertexCounter(&comboParts[NUMBER_COMBO], nCntPlace, INTERVAL_NUMBER);
		object->SetTextureCounter(&comboParts[NUMBER_COMBO], number, INTERVAL_NUMBER_TEXTURE);
	}	

	object->DrawObject(pDevice, &comboParts[TEXT_COMBO]);
	object->SetVertexObject(&comboParts[TEXT_COMBO]);
}

//=============================================================================
// 数字ボリュームアップエフェクト処理
//=============================================================================
void Combo::VolumeUpEffect(void)
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
void Combo::UpdateNumberColor(void)
{
	int firstColorStartCombo  = 0;
	int secondColorStartCombo = 5;
	int thirdColorStartCombo  = 10;

	if (combo >= firstColorStartCombo && combo < secondColorStartCombo)
	{
		object->SetColorObject(&comboParts[NUMBER_COMBO], SET_COLOR_NOT_COLORED);
	}
	if (combo >= secondColorStartCombo && combo < thirdColorStartCombo)
	{
		object->SetColorObject(&comboParts[NUMBER_COMBO], SET_COLOR_YELLOW);
	}
	if (combo >= thirdColorStartCombo)
	{
		object->SetColorObject(&comboParts[NUMBER_COMBO], SET_COLOR_RED);
	}
}
