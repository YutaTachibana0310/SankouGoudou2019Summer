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
#define COMBOPARTS_MAX		(3)

enum COMBO_PARTS
{
	NUMBER_COMBO,
	TEXT_COMBO,
	BACKGROUND_COMBO
};

#include "UIdrawer.h"

/**************************************
前方宣言
***************************************/
class ComboNumber;
class ComboText;
class ComboBG;

//*****************************************************************************
// 構造体定義
//*****************************************************************************
class Combo :public Object
{
public:
	ComboNumber * comboNumber;
	ComboText * comboText;
	ComboBG * comboBG;

	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

protected:
	int combo;
	int comboMax;
	bool volumeUpEffectUsed;

private:
	float radian;
	void VolumeUpEffect(void);
	void UpdateNumberColor(void);
};

class ComboNumber :public Combo
{
};

class ComboText :public Combo
{
};

class ComboBG :public Combo
{
};

#endif