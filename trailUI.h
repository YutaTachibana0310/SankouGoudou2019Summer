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
�O���錾
***************************************/
class Object;

//*****************************************************************************
// �\���̒�`
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

	// �ǂݍ��ރe�N�X�`���t�@�C����
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

