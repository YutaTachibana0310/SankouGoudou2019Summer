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

#include "GameSceneUIManager.h"
#include "UIdrawer.h"

/**************************************
前方宣言
***************************************/
class Object;
class GameSceneUI;
class TelopBG;

//*****************************************************************************
// 構造体定義
//*****************************************************************************
class BattleStartTelop :public Object
{
public:
	Object*object;
	TelopBG*telopBG;
	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//テロップセット関数
	void SetBattleStartTelop(void);
};

#endif
