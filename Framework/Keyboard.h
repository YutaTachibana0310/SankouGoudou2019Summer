//=====================================
//
//�L�[�{�[�h�w�b�_[Keyboard.h]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _KEYBOARD_H_
#define _KEYBOARD_H_

#include "../main.h"

/**************************************
�}�N����`
***************************************/

/**************************************
�N���X��`
***************************************/

/**************************************
�v���g�^�C�v�錾
***************************************/
HRESULT InitKeyboard(HINSTANCE hInst, HWND hWnd, LPDIRECTINPUT8 inputInterface);
void UninitKeyboard();
HRESULT UpdateKeyboard(void);

bool GetKeyboardPress(int nKey);
bool GetKeyboardTrigger(int nKey);
bool GetKeyboardRepeat(int nKey);
bool GetKeyboardRelease(int nKey);

#endif	