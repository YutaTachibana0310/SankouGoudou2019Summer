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
#define	ADRESS_TEXTURE_TEXT_COMBO	"data/TEXTURE/UI/comboText.png"	// 読み込むテクスチャファイル名

enum COMBO_PARTS
{
	NUMBER_COMBO,
	TEXT_COMBO,
};

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitCombo	(void);
void	UninitCombo	(void);
void	UpdateCombo	(void);
void	DrawCombo	(void);
void	ChangeCombo	(int value);

#endif