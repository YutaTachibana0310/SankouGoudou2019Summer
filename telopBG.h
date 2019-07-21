//=============================================================================
//
// テロップ背景処理 [telopBG.h]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#ifndef _TELOP_BG_H_
#define _TELOP_BG_H_

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	ADRESS_TEXTURE_TELOP_BG	("data/TEXTURE/UI/telop/telopBG.png")	// 読み込むテクスチャファイル名

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitTelopBG(void);
void UninitTelopBG(void);
void UpdateTelopBG(void);
void DrawTelopBG(void);

void AvctivateTelopBGOpen(void);
void AvctivateTelopBGClose(void);

bool GetTelopBGOpenActive(void);
bool GetTelopBGCloseActive(void);

#endif
