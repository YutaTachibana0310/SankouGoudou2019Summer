//=============================================================================
//
// タイトルロゴ画面処理 [titleLogoUI.h]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#ifndef _TITLELOGO_H_
#define _TITLELOGO_H_
#include "UIdrawer.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	ADRESS_TEXTURE_TITLELOGO	("data/TEXTURE/UI/チームロゴ.png")	// 読み込むテクスチャファイル名

#include "TitleSceneUIManager.h"

class Object;

/**************************************
前方宣言
***************************************/
class TitleSceneUI;

//*****************************************************************************
// 構造体定義
//*****************************************************************************
class TitleLogo :public TitleSceneUI
{
public:
	Object *object;
	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
};

#endif

