//=============================================================================
//
// �R���{���� [combo.h]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#ifndef _COMBO_H_
#define _COMBO_H_

/**************************************
�O���錾
***************************************/
class Object;
class CounterObject;
class RotateObject;

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
class Combo
{
public:
	Combo();
	~Combo();

	CounterObject * number;
	Object * text;
	RotateObject * bg;

	void Update(void);
	void Draw(void);

	int combo;
	int comboMax;
	bool volumeUpEffectUsed;

private:
	float radian;
	void VolumeUpEffect(void);
	void UpdateNumberColor(void);
};


#endif