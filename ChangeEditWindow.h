//=====================================
//
//Change型エディットウィンドウヘッダ[ChangeEditWindow.h]
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _CHANGEEDITWINDOW_H_
#define _CHANGEEDITWINDOW_H_

#include "main.h"
#include "BaseEditWindow.h"

/**************************************
マクロ定義
***************************************/

/**************************************
クラス定義
***************************************/
class ChangeEditWindow : public DataEditWindow
{
public:
	bool Draw();
	picojson::value Serialize();
	void Deserialize(picojson::object data);

	ChangeEditWindow() {}
	~ChangeEditWindow() {}

private:
	int start;
	int end;
};

#endif