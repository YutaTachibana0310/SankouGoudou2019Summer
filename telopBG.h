//=============================================================================
//
// テロップ背景処理 [telopBG.h]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#ifndef _TELOP_BG_H_
#define _TELOP_BG_H_
#include "UIdrawer.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	ADRESS_TEXTURE_TELOP_BG	("data/TEXTURE/UI/telop/telopBG.png")	// 読み込むテクスチャファイル名

#include "GameSceneUIManager.h"
#include "UIdrawer.h"

class Object;

/**************************************
前方宣言
***************************************/
class GameSceneUI;

//*****************************************************************************
// 構造体定義
//*****************************************************************************
class TelopBG :public Object
{
public:
	Object *object;
	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void AvctivateTelopBGOpen(void);
	void AvctivateTelopBGClose(void);

	bool GetTelopBGOpenActive(void);
	bool GetTelopBGCloseActive(void);

private:
	void OpenTelopBG(void);
	void CloseTelopBG(void);

	void SetEasingValueTelopBGOpen(void);
	void SetEasingValueTelopBGClose(void);
};

#endif
