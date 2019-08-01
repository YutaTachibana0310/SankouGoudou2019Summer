//=============================================================================
//
// タイトル背景画面処理 [titleBGUI.h]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#ifndef _TITLEBG_H_
#define _TITLEBG_H_
#include "UIdrawer.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	ADRESS_TEXTURE_TITLEBG	("data/TEXTURE/UI/title_test.jpg")	// 読み込むテクスチャファイル名

#include "TitleSceneUIManager.h"
#include "UIdrawer.h"

class Object;

/**************************************
前方宣言
***************************************/
class TitleSceneUI;

//*****************************************************************************
// 構造体定義
//*****************************************************************************
class TitleBG :public TitleSceneUI
{
public:
	Object *object;
	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
};

#endif