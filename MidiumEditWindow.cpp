//=====================================
//
//MidiumEditWindow.cpp
//機能:中型エネミーの出現データエディタ
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "MidiumEditWindow.h"
#include "debugWindow.h"

/**************************************
グローバル変数
***************************************/

/**************************************
描画処理
***************************************/
bool MidiumEditWindow::Draw()
{
	bool selected = false;
	
	//ラベル表示
	DebugText("ModelList");

	//データ追加ボタン
	if (DebugButton("Add"))
	{
		startList.push_back(0);
		goalList.push_back(0);
	}

	//データ削除ボタン
	if (DebugButton("Remove"))
	{
		startList.pop_back();
		goalList.pop_back();
	}

	//各データを入力
	for (UINT i = 0; i < startList.size(); i++)
	{
		std::string label = std::string("##") + "start" + std::to_string(i);
		selected |= DebugInputInt(label.c_str(), &startList[i]);

		DebugSameLine();
		label = std::string("##") + "end" + std::to_string(i);
		selected |= DebugInputInt(label.c_str(), &goalList[i]);
	}

	return selected;
}

/**************************************
シリアライズ処理
***************************************/
picojson::value MidiumEditWindow::Serialize()
{
	picojson::array dataList;

	for (UINT i = 0; i < startList.size(); i++)
	{
		picojson::object data;
		data.emplace(std::make_pair("start", picojson::value((double)startList[i])));
		data.emplace(std::make_pair("end", picojson::value((double)goalList[i])));
		dataList.push_back(picojson::value(data));
	}

	picojson::object returnVal;
	returnVal.emplace(std::make_pair("dataList", picojson::value(dataList)));
	return picojson::value(returnVal);
}

/**************************************
デシリアライズ処理
***************************************/
void MidiumEditWindow::Deserialize(picojson::object data)
{
	picojson::array dataList = data["dataList"].get<picojson::array>();

	startList.clear();
	goalList.clear();

	for (UINT i = 0; i < dataList.size(); i++)
	{
		int start = static_cast<int>(dataList[i].get<picojson::object>()["start"].get<double>());
		int end = static_cast<int>(dataList[i].get<picojson::object>()["end"].get<double>());

		startList.push_back(start);
		goalList.push_back(end);
	}
}
