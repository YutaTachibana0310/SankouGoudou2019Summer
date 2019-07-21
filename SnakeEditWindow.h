//=====================================
//
//スネークエディットウィンドウヘッダ[SnakeEditWindow.h]
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _SNAKEEDITWINDOW_H_
#define _SNAKEEDITWINDOW_H_

#include "main.h"
#include "DataEditWindow.h"

/**************************************
マクロ定義
***************************************/

/**************************************
クラス定義
***************************************/
class SnakeEditWindow : public DataEditWindow
{
public:
	SnakeEditWindow() {}
	~SnakeEditWindow() {}

	bool Draw();
	picojson::value Serialize();
	void Deserialize(picojson::object data);

private:
	std::vector<int> destList;
};

#endif