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

#include "GameSceneUIManager.h"
#include "UIdrawer.h"

class Object;

/**************************************
前方宣言
***************************************/
class GameSceneUI;
class TelopBG;

//*****************************************************************************
// 構造体定義
//*****************************************************************************
class StageClearTelop :public GameSceneUI
{
public:
	Object *object;
	TelopBG *telopBG;
	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//テロップセット関数
	void SetStageClearTelop(void);
};


#endif
