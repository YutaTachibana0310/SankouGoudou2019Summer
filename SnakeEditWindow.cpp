//=====================================
//
//スネークエディットウィンドウ処理[SnakeEditWindow.cpp]
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "SnakeEditWindow.h"
#include "debugWindow.h"

using namespace std;

/**************************************
マクロ定義
***************************************/

/**************************************
描画処理
***************************************/
bool SnakeEditWindow::Draw()
{
	bool selected = false;

	string destLabel = string("destList");

	//destListと表示
	DebugText(destLabel.c_str());

	//データ追加ボタン
	if (DebugButton("Add")) destList.push_back(0);
	
	//データ削除ボタン
	DebugSameLine();
	if (DebugButton("Remove") && destList.size() > 0)
	{
		destList.pop_back();
	}

	//各データを入力
	for (UINT i = 0; i < destList.size(); i++)
	{
		string label = string("##") + destLabel + to_string(i);
		selected |= DebugInputInt(label.c_str(), &destList[i]);

		destList[i] = Clamp(0, 4, destList[i]);
	}

	return selected;
}

/**************************************
シリアライズ処理
***************************************/
picojson::value SnakeEditWindow::Serialize()
{
	picojson::array dataList;

	for (auto& dest : destList)
	{
		picojson::object data;
		data.emplace(make_pair("dest", picojson::value((double)dest)));
		dataList.push_back(picojson::value(data));
	}

	picojson::object returnVal;
	returnVal.emplace(make_pair("destList", picojson::value(dataList)));
	return picojson::value(returnVal);
}

/**************************************
デシリアライズ処理
***************************************/
void SnakeEditWindow::Deserialize(picojson::object data)
{
	picojson::array dataList = data["destList"].get<picojson::array>();

	destList.clear();
	destList.resize(dataList.size());

	for (UINT i = 0; i < destList.size(); i++)
	{
		destList[i] = static_cast<int>(dataList[i].get<picojson::object>()["dest"].get<double>());
	}
}
