//=============================================================================
//
// スタートボタン画面処理 [startButtonUI.h]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#ifndef _STARTBUTTON_H_
#define _STARTBUTTON_H_

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	ADRESS_TEXTURE_STARTBUTTON_BG	("data/TEXTURE/UI/startButtonBG.png")	// 読み込むテクスチャファイル名
#define	ADRESS_TEXTURE_STARTBUTTON_TEXT	("data/TEXTURE/UI/startButtonText.png")	// 読み込むテクスチャファイル名

enum STARTBUTTON_PARTS
{
	BACKGROUND_STARTBUTTON,
	TEXT_STARTBUTTON,
};

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitStartButton(void);
void	UninitStartButton(void);
void	UpdateStartButton(void);
void	DrawStartButton(void);

#endif

