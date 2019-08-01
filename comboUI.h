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

enum COMBO_PARTS
{
	NUMBER_COMBO,
	TEXT_COMBO,
	BACKGROUND_COMBO
};

#include "GameSceneUIManager.h"
#include "UIdrawer.h"

class Object;

/**************************************
�O���錾
***************************************/
class GameSceneUI;

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
class Combo :public GameSceneUI
{
public:
	Object*object;
	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void AddCombo(int value);
	void SetCombo(int value);

private:
	void UpdateNumberColor(void);
};

#endif