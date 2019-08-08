//=====================================
//
//ボンバーストックエフェクトヘッダ[BomberStockEffect.h]
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _BOMBERSTOCKEFFECT_H_
#define _BOMBERSTOCKEFFECT_H_

#include "main.h"
#include "Framework\BoardPolygon.h"

/**************************************
マクロ定義
***************************************/

/**************************************
クラス定義
***************************************/
class BomberStockEffect
{
public:
	BomberStockEffect();
	~BomberStockEffect();

	void Init();
	void Update();
	void Draw();

	Transform transform;

private:
	bool active;
	int cntFrame;
	BoardPolygon* polygon;
};

#endif