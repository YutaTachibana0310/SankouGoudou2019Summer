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
#define	ADRESS_TEXTURE_TEXT_COMBO	"data/TEXTURE/UI/comboText.png"	// �ǂݍ��ރe�N�X�`���t�@�C����

enum COMBO_PARTS
{
	NUMBER_COMBO,
	TEXT_COMBO,
};

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitCombo	(void);
void	UninitCombo	(void);
void	UpdateCombo	(void);
void	DrawCombo	(void);
void	ChangeCombo	(int value);

#endif