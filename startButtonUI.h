//=============================================================================
//
// �X�^�[�g�{�^����ʏ��� [startButtonUI.h]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#ifndef _STARTBUTTON_H_
#define _STARTBUTTON_H_

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	ADRESS_TEXTURE_STARTBUTTON_BG	("data/TEXTURE/UI/startButtonBG.png")	// �ǂݍ��ރe�N�X�`���t�@�C����
#define	ADRESS_TEXTURE_STARTBUTTON_TEXT	("data/TEXTURE/UI/startButtonText.png")	// �ǂݍ��ރe�N�X�`���t�@�C����

enum STARTBUTTON_PARTS
{
	BACKGROUND_STARTBUTTON,
	TEXT_STARTBUTTON,
};

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitStartButton(void);
void	UninitStartButton(void);
void	UpdateStartButton(void);
void	DrawStartButton(void);

#endif

