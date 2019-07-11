//=====================================
//
//ベースエディットウィンドウ処理[BaseEditWindow.cpp]
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "BaseEditWindow.h"
#include "debugWindow.h"
#include <algorithm>

using namespace std;

/**************************************
マクロ定義
***************************************/

/**************************************
構造体定義
***************************************/

/**************************************
static変数
***************************************/
UINT BaseEditWindow::instanceCount;

/**************************************
コンストラクタ
***************************************/
BaseEditWindow::BaseEditWindow()
{
	id = instanceCount++;
	frame = 0;
	
}

/**************************************
デストラクタ
***************************************/
BaseEditWindow::~BaseEditWindow()
{
	instanceCount--;
	for (auto pair : dataWindow)
	{
		SAFE_DELETE(pair.second);
	}
	dataWindow.clear();

}
/**************************************
描画処理
***************************************/
void BaseEditWindow::Draw()
{
	string windowName = to_string(id);
	BeginDebugWindow(windowName.c_str());

	DebugInputInt("frame", &frame);
	DebugInputText("type", &type);

	if (dataWindow.count(type) != 0)
	{
		dataWindow[type]->Draw();
	}

	EndDebugWindow(windowName.c_str());
}

/**************************************
シリアライズ処理
***************************************/
picojson::value BaseEditWindow::Serialize()
{
	picojson::object obj;

	obj.emplace(make_pair("id", picojson::value((double)id)));
	obj.emplace(make_pair("frame", picojson::value((double)frame)));

	if (dataWindow.count(type) != 0)
	{
		obj.emplace(make_pair("data", dataWindow[type]->Serialize()));
	}

	return picojson::value(obj);
}