//=============================================================================
//
// �R���{���� [combo.h]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#ifndef _COMBO_H_
#define _COMBO_H_

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	ADRESS_TEXTURE_NUMBER_COMBO	"data/TEXTURE/UI/number.png"	// �ǂݍ��ރe�N�X�`���t�@�C����
#define	ADRESS_TEXTURE_TEXT_COMBO	"data/TEXTURE/UI/combo/comboText.png"	// �ǂݍ��ރe�N�X�`���t�@�C����
#define	ADRESS_TEXTURE_BACKGROUND_COMBO	"data/TEXTURE/UI/combo/circleCombo.png"	// �ǂݍ��ރe�N�X�`���t�@�C����

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
�O���錾
***************************************/
class ComboNumber;
class ComboText;
class ComboBG;

//*****************************************************************************
// �\���̒�`
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