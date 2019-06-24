//=============================================================================
//
// カーソル画面処理 [cursor.h]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#ifndef _CURSOR_H_
#define _CURSOR_H_

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	ADRESS_TEXTURE_CURSOR	("data/TEXTURE/UI/cursor.png")	// 読み込むテクスチャファイル名

#define COLLIDERSIZE_CURSOR (D3DXVECTOR3(5.0f,5.0f,0.0f))

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitCursor(void);
void	UninitCursor(void);
void	UpdateCursor(HWND hWnd);
void	DrawCursor(void);
bool	IsCursorOverd(HWND hWnd, D3DXVECTOR3 pos, D3DXVECTOR3 size);

#endif
