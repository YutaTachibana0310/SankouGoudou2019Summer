//=============================================================================
//
// �ړ�������ʏ��� [trail.h]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#ifndef _TRAIL_H_
#define _TRAIL_H_

//*****************************************************************************
// �}�N����`
//*****************************************************************************
// �ǂݍ��ރe�N�X�`���t�@�C����
#define	ADRESS_TEXTURE_TRAIL_BG	("data/TEXTURE/UI/trail/trailBG.png")
#define	ADRESS_TEXTURE_TRAIL_LINE_TOP_TO_LOWERLEFT	("data/TEXTURE/UI/trail/trailLine_TopToLowerLeft.png")
#define	ADRESS_TEXTURE_TRAIL_LINE_TOP_TO_LOWERRIGHT	("data/TEXTURE/UI/trail/trailLine_TopToLowerRight.png")
#define	ADRESS_TEXTURE_TRAIL_LINE_LOWERLELEFT_TO_MIDDLERIGHT ("data/TEXTURE/UI/trail/trailLine_LowerLeftToMiddleRight.png")
#define	ADRESS_TEXTURE_TRAIL_LINE_LOWERRIGHT_TO_MIDDLELEFT	("data/TEXTURE/UI/trail/trailLine_LowerRightToMiddleLeft.png")
#define	ADRESS_TEXTURE_TRAIL_LINE_MIDDLELEFT_TO_MIDDLERIGHT	("data/TEXTURE/UI/trail/trailLine_MiddleLeftToMiddleRight.png")

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

#include "GameSceneUIManager.h"
#include "UIdrawer.h"

class Object;

/**************************************
�O���錾
***************************************/
class GameSceneUI;

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
class Trail :public Object
{
public:
	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	Trail * trail[TRAILPARTS_MAX];

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

