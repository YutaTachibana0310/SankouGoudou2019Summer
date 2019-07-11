//=============================================================================
//
// バトルスタートテロップ処理 [battleStartTelop.h]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#ifndef _BATTLE_START_TELOP_H_
#define _BATTLE_START_TELOP_H_

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	ADRESS_TEXTURE_BATTLE_START_TELOP	("data/TEXTURE/UI/telop/battleStartTelop.png")	// 読み込むテクスチャファイル名

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitBattleStartTelop(void);
void	UninitBattleStartTelop(void);
void	UpdateBattleStartTelop(void);
void	DrawBattleStartTelop(void);

#endif
