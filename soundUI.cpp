//=============================================================================
//
// サウンドUI処理 [soundUI.cpp]
// Author : 渡邉良則
//
//=============================================================================
#include "main.h"
#include "soundUI.h"
#include "UIdrawer.h"
#include "sound.h"

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//*****************************************************************************
// グローバル変数
//*****************************************************************************
OBJECT	sounduiParts[SOUNDUI_PARTS_MAX];
int		currentNum;
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitSoundUI(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//基本のサウンドマーク
	LoadTexture(pDevice, ADRESS_TEXTURE_SOUNDUI_MARK, &sounduiParts[SOUND_MARK]);
	sounduiParts[SOUND_MARK].position = POSITION_SOUNDUI;
	sounduiParts[SOUND_MARK].size = SIZE_SOUNDUI;
	sounduiParts[SOUND_MARK].use = true;

	//ミュート時のマーク
	LoadTexture(pDevice, ADRESS_TEXTURE_SOUNDUI_MUTE, &sounduiParts[SOUND_MUTE]);
	sounduiParts[SOUND_MUTE].position = POSITION_SOUNDUI;
	sounduiParts[SOUND_MUTE].size = SIZE_SOUNDUI;
	sounduiParts[SOUND_MUTE].use = false;

	//音量の大きさを表す波形ライン
	for (int i = SOUND_LINE_ONE; i < SOUNDUI_PARTS_MAX; i++)
	{
		LoadTexture(pDevice, ADRESS_TEXTURE_SOUNDUI_LINE, &sounduiParts[i]);
		sounduiParts[i].size.x = SIZE_SOUNDLINE_X;
		sounduiParts[i].size.y = SIZE_SOUNDLINE_Y + i * 10;
		sounduiParts[i].size.z = SIZE_SOUNDLINE_Z;

		sounduiParts[i].position.x = POSITION_SOUNDLINE_X + i * 30;
		sounduiParts[i].position.y = POSITION_SOUNDLINE_Y;
		sounduiParts[i].position.z = POSITION_SOUNDLINE_Z;
		sounduiParts[i].use = true;
	}

	for (int i = 0; i < SOUNDUI_PARTS_MAX; i++)
	{
		InitialTexture(&sounduiParts[i]);
		MakeVertexObject(&sounduiParts[i]);

		sounduiParts[i].rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		SetColorObject(&sounduiParts[i], SET_COLOR_NOT_COLORED);

	}

	currentNum = Sound::GetInstance()->UIcounta;

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitSoundUI(void)
{
	for (int i = 0; i < SOUNDUI_PARTS_MAX; i++)
	{
		ReleaseTexture(&sounduiParts[i]);
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateSoundUI(void)
{
	if (currentNum <= SOUND_LINE_ONE) {
		sounduiParts[SOUND_MARK].use = false;
		sounduiParts[SOUND_MUTE].use = true;
	}
	else{
		sounduiParts[SOUND_MARK].use = true;
		sounduiParts[SOUND_MUTE].use = false;
	}
	//音量を下げる場合
	if (currentNum >= Sound::GetInstance()->UIcounta) {
		sounduiParts[currentNum].use = false;
		currentNum = Sound::GetInstance()->UIcounta;
	}
	//音量を上げる場合
	else if (currentNum < Sound::GetInstance()->UIcounta) {
		sounduiParts[currentNum].use = true;
		currentNum = Sound::GetInstance()->UIcounta;
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawSoundUI(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int i = 0; i < SOUNDUI_PARTS_MAX; i++)
	{
		if (sounduiParts[i].use) {
			DrawObject(pDevice, sounduiParts[i]);
			SetVertexObject(&sounduiParts[i]);
		}
	}
}

