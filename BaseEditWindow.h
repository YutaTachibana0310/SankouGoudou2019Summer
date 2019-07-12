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
	BaseEditWindow(int id, int frame, std::string type, picojson::object data);
	~BaseEditWindow();

	bool Draw();
	picojson::value Serialize();

	int id;
	int frame;
	std::string type;

private:

	std::map<std::string, DataEditWindow*> dataWindow;

	void CreateEditWindow();

	static UINT instanceCount;
};

#endif