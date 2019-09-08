//=====================================
//
//MidiumEditWindow.h
//機能:中型エネミーの出現データエディタ
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _MIDIUMEDITWINDOW_H_
#define _MIDIUMEDITWINDOW_H_

#include "main.h"
#include "BaseEditWindow.h"

/**************************************
前方宣言
***************************************/

/**************************************
クラス定義
***************************************/
class MidiumEditWindow : public DataEditWindow
{
	using DataEditWindow::DataEditWindow;
public:
	bool Draw();
	picojson::value Serialize();
	void Deserialize(picojson::object data);

private:
	std::vector<int> startList;
	std::vector<int> goalList;
};
#endif