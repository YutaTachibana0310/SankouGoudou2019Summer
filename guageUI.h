//=============================================================================
//
// ゲージ画面処理 [guage.h]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#ifndef _GUAGE_H_
#define _GUAGE_H_

/**************************************
前方宣言
***************************************/
class Object;
class GuageObject;
class Viewer3D;

//*****************************************************************************
// 構造体定義
//*****************************************************************************
class Guage
{
public:
	Guage();
	~Guage();

	void Update(void);
	void Draw(void);

	int maxHp;
	float trueGuagePercentage;	//実際のゲージパーセンテージ

private:
	GuageObject *damageGuage;
	GuageObject *hPGuage;
	Object *frame;
	Object *bg;
	Viewer3D * viewer;

	float	damageGuagePercentage;	//ダメージ表現ゲージパーセンテージ
};

#endif

