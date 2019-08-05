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

/**************************************
前方宣言
***************************************/
class DamageGuage;
class HPGuage;
class GuageFlame;
class GuageText;

//*****************************************************************************
// 構造体定義
//*****************************************************************************
class Guage :public Object
{
public:
	DamageGuage *damageGuage;
	HPGuage		*hPGuage;
	GuageFlame  *guageFlame;
	GuageText	*guageText;

	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void ChangeGuage(float value);

private:
	float	damageGuagePercentage;	//ダメージ表現ゲージパーセンテージ
	float	trueGuagePercentage;	//実際のゲージパーセンテージ
};

class DamageGuage :public Guage
{

};

class HPGuage :public Guage
{

};

class GuageFlame :public Guage
{

};

class GuageText :public Guage
{

};

#endif

