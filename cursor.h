//=============================================================================
//
// �J�[�\����ʏ��� [cursor.h]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#ifndef _CURSOR_H_
#define _CURSOR_H_

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	ADRESS_TEXTURE_CURSOR	("data/TEXTURE/UI/cursor.png")	// �ǂݍ��ރe�N�X�`���t�@�C����

#define COLLIDERSIZE_X_CURSOR (5)
#define COLLIDERSIZE_Y_CURSOR (5)

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitCursor(void);
void	UninitCursor(void);
void	UpdateCursor(HWND hWnd);
void	DrawCursor(void);

#endif
