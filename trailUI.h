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

#define	TRAILPARTS_MAX	(6)

enum TRAIL_PARTS
{
	TRAIL_BG,
	TRAIL_LINE_TOP_TO_LOWERLEFT,
	TRAIL_LINE_TOP_TO_LOWERRIGHT,
	TRAIL_LINE_LOWERLEFT_TO_MIDDLERIGHT,
	TRAIL_LINE_LOWERRIGHT_TO_MIDDLELEFT,
	TRAIL_LINE_MIDDLELEFT_TO_MIDDLERIGHT,
};

/**************************************
前方宣言
***************************************/
class Object;

//*****************************************************************************
// 構造体定義
//*****************************************************************************
class Trail
{
public:
	Trail();
	~Trail();

	void Update(void);
	void Draw(void);

private:
	Object * trail[TRAILPARTS_MAX];

	// 読み込むテクスチャファイル名
	const char *texPath[TRAILPARTS_MAX]
	{
		"data/TEXTURE/UI/trail/trailBG.png",
		"data/TEXTURE/UI/trail/trailLine_TopToLowerLeft.png",
		"data/TEXTURE/UI/trail/trailLine_TopToLowerRight.png",
		"data/TEXTURE/UI/trail/trailLine_LowerLeftToMiddleRight.png",
		"data/TEXTURE/UI/trail/trailLine_LowerRightToMiddleLeft.png",
		"data/TEXTURE/UI/trail/trailLine_MiddleLeftToMiddleRight.png"
	};
};

#endif

