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

enum TELOP_ANIM_SCENE
{
	WAIT_BG_OPEN,
	IN_TEXT,
	STOP_TEXT,
	OUT_TEXT,
	WAIT_BG_CLOSE
};

/**************************************
前方宣言
***************************************/
class Object;

//*****************************************************************************
// 構造体定義
//*****************************************************************************
class TelopBG
{
public:
	TelopBG();
	~TelopBG();

	void Update(void);
	void Draw(void);

	//テロップ開閉開始処理
	void AvctivateTelopBGOpen(void);
	void AvctivateTelopBGClose(void);

	bool GetTelopBGOpenActive(void);
	bool GetTelopBGCloseActive(void);

private:
	Object * telopBG;

	float percentage;

	float easingStart;
	float easingGoal;

	void OpenTelopBG(void);
	void CloseTelopBG(void);

	void SetVertex(float percentage);

	void SetEasingValueTelopBGOpen(void);
	void SetEasingValueTelopBGClose(void);
};

#endif
