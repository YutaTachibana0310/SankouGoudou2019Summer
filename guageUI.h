//=============================================================================
//
// ゲージ画面処理 [guage.h]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#ifndef _GUAGE_H_
#define _GUAGE_H_

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	ADRESS_TEXTURE_GUAGEBAR		("data/TEXTURE/UI/guage/guageBar_vertical.png")		
#define	ADRESS_TEXTURE_GUAGEFLAME	("data/TEXTURE/UI/guage/guageFrame_vertical.png")		
#define	ADRESS_TEXTURE_GUAGETEXT	("data/TEXTURE/UI/guage/guageText_fever_vertical.png")		

enum GUARGE_PARTS
{
	GUAGEBAR_DAMAGE,  // ダメージ表現ゲージバー
	GUAGEBAR_TRUE,	  // 実際のゲージバー
	GUAGEFLAME,
	GUAGETEXT,
};

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
class Guage :public Object
{
public:
	Object*object;
	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void ChangeGuage(float value);
};


#endif

