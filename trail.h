//=============================================================================
//
// 移動履歴画面処理 [trail.h]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#ifndef _TRAIL_H_
#define _TRAIL_H_

//*****************************************************************************
// マクロ定義
//*****************************************************************************

// 読み込むテクスチャファイル名
#define	ADRESS_TEXTURE_TRAIL_BG	("data/TEXTURE/UI/trail/trailBG.png")
#define	ADRESS_TEXTURE_TRAIL_LINE_TOP_TO_LOWERLELEFT	("data/TEXTURE/UI/trail/trailLine_TopToLowerLeft.png")
#define	ADRESS_TEXTURE_TRAIL_LINE_TOP_TO_LOWERRIGHT	("data/TEXTURE/UI/trail/trailLine_TopToLowerRight.png")
#define	ADRESS_TEXTURE_TRAIL_LINE_LOWERLELEFT_TO_MIDDLERIGHT ("data/TEXTURE/UI/trail/trailLine_LowerLeftToMiddleRight.png")
#define	ADRESS_TEXTURE_TRAIL_LINE_LOWERRIGHT_TO_MIDDLELEFT	("data/TEXTURE/UI/trail/trailLine_LowerRightToMiddleLeft.png")
#define	ADRESS_TEXTURE_TRAIL_LINE_MIDDLELEFT_TO_MIDDLERIGHT	("data/TEXTURE/UI/trail/trailLine_MiddleLeftToMiddleRight.png")

enum TRAIL_PARTS
{
	TRAIL_BG,
	TRAIL_LINE_TOP_TO_LOWERLELEFT,
	TRAIL_LINE_TOP_TO_LOWERRIGHT,
	TRAIL_LINE_LOWERLELEFT_TO_MIDDLERIGHT,
	TRAIL_LINE_LOWERRIGHT_TO_MIDDLELEFT,
	TRAIL_LINE_MIDDLELEFT_TO_MIDDLERIGHT,
};

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitTrail(void);
void	UninitTrail(void);
void	UpdateTrail(void);
void	DrawTrail(void);

#endif

