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
クラス定義
***************************************/
class DataEditWindow
{
public:
	DataEditWindow() {}
	virtual ~DataEditWindow() {}

	virtual void Draw() = 0;
	virtual picojson::value Serialize() = 0;
};

#endif