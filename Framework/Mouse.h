//=====================================
//
//テンプレートヘッダ[Template.h]
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _TEMPLATE_H_
#define _TEMPLATE_H_

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
HRESULT InitializeMouse(HINSTANCE hInst, HWND hWindow, LPDIRECTINPUT8 inputInterface); // マウスの初期化
void UninitMouse();						// マウスの終了処理
HRESULT UpdateMouse();					// マウスの更新処理

//---------------------------- mouse
BOOL IsMouseLeftPressed(void);      // 左クリックした状態
BOOL IsMouseLeftTriggered(void);    // 左クリックした瞬間
BOOL IsMouseRightPressed(void);     // 右クリックした状態
BOOL IsMouseRightTriggered(void);   // 右クリックした瞬間
BOOL IsMouseCenterPressed(void);    // 中クリックした状態
BOOL IsMouseCenterTriggered(void);  // 中クリックした瞬間
float GetMouseX(void);               // マウスがX方向に動いた相対値
float GetMouseY(void);               // マウスがY方向に動いた相対値
float GetMouseZ(void);               // マウスホイールが動いた相対値

D3DXVECTOR3 GetMousePosition(HWND hWnd);

#endif