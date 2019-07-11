//=====================================
//
//ベースエディットウィンドウヘッダ[BaseEditWindow.h]
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _BASEEDITWINDOW_H_
#define _BASEEDITWINDOW_H_

#include "main.h"
#include "DataEditWindow.h"
#include <map>
#include "picojson\picojson.h"

/**************************************
マクロ定義
***************************************/

/**************************************
クラス定義
***************************************/
class BaseEditWindow
{
public:
	BaseEditWindow();
	~BaseEditWindow();

	void Draw();
	picojson::value Serialize();

private:
	int id;
	int frame;
	std::string type;
	std::map<std::string, DataEditWindow*> dataWindow;

	static UINT instanceCount;
};

#endif