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

#define COLLIDERSIZE_CURSOR (D3DXVECTOR3(5.0f,5.0f,0.0f))

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitCursor(void);
void	UninitCursor(void);
void	UpdateCursor(HWND hWnd);
void	DrawCursor(void);
bool	IsCursorOverd(HWND hWnd, D3DXVECTOR3 pos, D3DXVECTOR3 size);

#endif
