//=====================================
//
//Change型エディットウィンドウ処理[ChangeEditWIndow.cpp]
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "ChangeEditWindow.h"
#include "debugWindow.h"

using namespace std;

/**************************************
マクロ定義
***************************************/

/**************************************
構造体定義
***************************************/

/**************************************
描画処理
***************************************/
void ChangeEditWindow::Draw(UINT id)
{
	string startLabel = string("start") + to_string(id);
	DebugInputInt(startLabel.c_str(), &start);

	string endLabel = string("end") + to_string(id);
	DebugInputInt(endLabel.c_str(), &end);

	start = Clamp(0, 5, start);
	end = Clamp(0, 5, end);
}

/**************************************
シリアライズ処理
***************************************/
picojson::value ChangeEditWindow::Serialize()
{
	picojson::object obj;
	obj.emplace(make_pair("start", picojson::value((double)start)));
	obj.emplace(make_pair("end", picojson::value((double)end)));

	return picojson::value(obj);
}

/**************************************
デシリアライズ処理
***************************************/
void ChangeEditWindow::Deserialize(picojson::object data)
{
	this->start = static_cast<int>(data["start"].get<double>());
	this->end = static_cast<int>(data["end"].get<double>());
}