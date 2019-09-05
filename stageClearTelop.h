//=============================================================================
//
// ステージクリアテロップ処理 [stageClearTelop.h]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#ifndef _STAGE_CLEAR_TELOP_H_
#define _STAGE_CLEAR_TELOP_H_

/**************************************
前方宣言
***************************************/
class TelopObject;
class TelopBG;

//*****************************************************************************
// 構造体定義
//*****************************************************************************
class StageClearTelop
{
public:
	StageClearTelop();
	~StageClearTelop();

	void Update(void);
	void Draw(void);

	bool isStageClearTelopActivated = false;

private:
	TelopObject * stageClearTelop;
	TelopBG *telopBG;

};


#endif
