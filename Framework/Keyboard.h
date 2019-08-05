//=====================================
//
//キーボードヘッダ[Keyboard.h]
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _KEYBOARD_H_
#define _KEYBOARD_H_

#include "../main.h"

/**************************************
マクロ定義
***************************************/

/**************************************
クラス定義
***************************************/

/**************************************
プロトタイプ宣言
***************************************/
HRESULT InitKeyboard(HINSTANCE hInst, HWND hWnd, LPDIRECTINPUT8 inputInterface);
void UninitKeyboard();
HRESULT UpdateKeyboard(void);

bool GetKeyboardPress(int nKey);
bool GetKeyboardTrigger(int nKey);
bool GetKeyboardRepeat(int nKey);
bool GetKeyboardRelease(int nKey);

#endif	