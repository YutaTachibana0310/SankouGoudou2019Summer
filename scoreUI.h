//=============================================================================
//
// �X�R�A���� [score.h]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#ifndef _SCORE_H_
#define _SCORE_H_

#include "main.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	ADRESS_TEXTURE_SCORE		"data/TEXTURE/UI/number.png"	// �ǂݍ��ރe�N�X�`���t�@�C����

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitScore	(void);
void	UninitScore	(void);
void	UpdateScore	(void);
void	DrawScore	(void);
void	ChangeScore	(int value);

#endif