//=============================================================================
//
// バトルスタートテロップ処理 [battleStartTelop.h]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#ifndef _BATTLE_START_TELOP_H_
#define _BATTLE_START_TELOP_H_

/**************************************
前方宣言
***************************************/
class TelopObject;
class TelopBG;

//*****************************************************************************
// 構造体定義
//*****************************************************************************
class BattleStartTelop
{
public:
	BattleStartTelop();
	~BattleStartTelop();

	void Update(void);
	void Draw(void);

	bool isBattleStartTelopActivated = false;

private:
	TelopObject * battleStartTelop;
	TelopBG*telopBG;
};

#endif
