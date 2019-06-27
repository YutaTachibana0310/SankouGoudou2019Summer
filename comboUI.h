//=============================================================================
//
// コンボ処理 [combo.h]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#ifndef _COMBO_H_
#define _COMBO_H_

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	ADRESS_TEXTURE_NUMBER_COMBO	"data/TEXTURE/UI/number.png"	// 読み込むテクスチャファイル名
#define	ADRESS_TEXTURE_TEXT_COMBO	"data/TEXTURE/UI/combo/comboText.png"	// 読み込むテクスチャファイル名
#define	ADRESS_TEXTURE_BACKGROUND_COMBO	"data/TEXTURE/UI/combo/circleCombo.png"	// 読み込むテクスチャファイル名

#define SPEED_VOLUMEUP_NUMBER		(0.2f)

enum COMBO_PARTS
{
	NUMBER_COMBO,
	TEXT_COMBO,
	BACKGROUND_COMBO
};

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitCombo	(void);
void	UninitCombo	(void);
void	UpdateCombo	(void);
void	DrawCombo	(void);
void	AddCombo	(int value);
void	SetCombo(int value);

#endif