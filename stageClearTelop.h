//=============================================================================
//
// ステージクリアテロップ処理 [stageClearTelop.h]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#ifndef _STAGE_CLEAR_TELOP_H_
#define _STAGE_CLEAR_TELOP_H_

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	ADRESS_TEXTURE_STAGE_CLEAR_TELOP	("data/TEXTURE/UI/telop/stageClearTelop.png")	// 読み込むテクスチャファイル名

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitStageClearTelop(void);
void UninitStageClearTelop(void);
void UpdateStageClearTelop(void);
void DrawStageClearTelop(void);

//テロップセット関数
void SetStageClearTelop(void);

#endif
