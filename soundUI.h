//=============================================================================
//
// サウンドUI処理 [sounduiUI.h]
// Author : 渡邉良則
//
//=============================================================================
#ifndef _SOUNDUI_H_
#define _SOUNDUI_H_

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	ADRESS_TEXTURE_SOUNDUI_MARK	("data/TEXTURE/UI/sound/sound.png")	// 読み込むテクスチャファイル名
#define	ADRESS_TEXTURE_SOUNDUI_MUTE	("data/TEXTURE/UI/sound/sound_mute.png")	// 読み込むテクスチャファイル名
#define	ADRESS_TEXTURE_SOUNDUI_LINE	("data/TEXTURE/UI/sound/sound_line.png")	// 読み込むテクスチャファイル名

#define SOUNDUI_PARTS_MAX		(7)
#define SOUNDUI_PARTS_LINE		(5)
#define SIZE_SOUNDUI			(D3DXVECTOR3(50.0f,50.0f,0.0f))
#define SIZE_MUTEUI				(D3DXVECTOR3(70.0f,60.0f,0.0f))
#define SIZE_SOUNDLINE_X		(25.0f)
#define SIZE_SOUNDLINE_Y		(30.0f)
#define SIZE_SOUNDLINE_Z		(0.0f)

#define POSITION_SOUNDUI		(D3DXVECTOR3(SCREEN_WIDTH - 270.0f,100.0f,0.0f))
#define POSITION_SOUNDLINE_X	(SCREEN_WIDTH - 250.0f)
#define POSITION_SOUNDLINE_Y	(100.0f)
#define POSITION_SOUNDLINE_Z	(0.0f)

#define VOLUME_ZOOM					(30.0f)
#define INCREASE_VOLUME_ALPHA		(0.02f)

enum SOUNDUI_PARTS
{
	SOUND_MARK,
	SOUND_MUTE,
	SOUND_LINE_ONE,
	SOUND_LINE_TWO,
	SOUND_LINE_THREE,
	SOUND_LINE_FOUR,
	SOUND_LINE_FIVE
};

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitSoundUI(void);
void	UninitSoundUI(void);
void	UpdateSoundUI(void);
void	DrawSoundUI(void);

#endif

#pragma once
