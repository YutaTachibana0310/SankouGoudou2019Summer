//=====================================
//
//データエディットウィンドウヘッダ[DataEditWindow.h]
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _DATAEDITWINDOW_H_
#define _DATAEDITWINDOW_H_

#include "main.h"
#include "picojson\picojson.h"

/**************************************
マクロ定義
***************************************/

/**************************************
DataEditWindowクラス
継承先でDraw(), Serialize()を実装する
***************************************/
class DataEditWindow
{
public:
	DataEditWindow() {}
	virtual ~DataEditWindow() {}

	virtual void Draw(UINT id) = 0;
	virtual picojson::value Serialize() = 0;
};

#endif