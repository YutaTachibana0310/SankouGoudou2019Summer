//=============================================================================
//
// ボムストック画面処理 [bomberStockUI.h]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#ifndef _BOMBER_STOCK_H_
#define _BOMBER_STOCK_H_

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_STOCKED_BOM_NUM (3)

/**************************************
前方宣言
***************************************/
class Object;
class RotateObject;
class Viewer3D;

//*****************************************************************************
// 構造体定義
//*****************************************************************************
class BomberStock
{
public:
	BomberStock();
	~BomberStock();

	void Update(void);
	void Draw(void);

	//ストックされたボムの数
	int stockedBomNum;

private:
	RotateObject * bom[MAX_STOCKED_BOM_NUM];
	Object * bg;
	Viewer3D * viewer;
};

#endif
