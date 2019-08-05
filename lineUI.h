//=============================================================================
//
// インターフェースライン画面処理 [line.h]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#ifndef _LINE_H_
#define _LINE_H_

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	ADRESS_TEXTURE_LINE	("data/TEXTURE/UI/interfaceLine.png")	// 読み込むテクスチャファイル名

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
class Line:public Object
{
public:
	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
};

#endif
