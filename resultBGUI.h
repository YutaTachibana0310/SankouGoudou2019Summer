//=============================================================================
//
// リザルト背景画面処理 [resultBGUI.h]
// Author : 渡邉良則
//
//=============================================================================
#ifndef _RESULTBGUI_H_
#define _RESULTBGUI_H_

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	ADRESS_TEXTURE_RESULTBG	("data/TEXTURE/UI/Result/ブラック.jpg")	// 読み込むテクスチャファイル名

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitResultBG(void);
void	UninitResultBG(void);
void	UpdateResultBG(void);
void	DrawResultBG(void);

#endif
