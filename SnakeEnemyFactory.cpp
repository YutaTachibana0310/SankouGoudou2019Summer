//=====================================
//
//テンプレート処理[SnakeEnemyFactory.cpp]
//Author:GP12A332 21 立花雄太
//
//=====================================
#include "SnakeEnemyFactory.h"
#include "SnakeEnemyModel.h"

/**************************************
マクロ定義
***************************************/

/**************************************
エネミー生成処理
***************************************/
EnemyModel * SnakeEnemyFactory::Create(picojson::object & data)
{
	//インスタンス生成
	SnakeEnemyModel *model = new SnakeEnemyModel();

	//配列データをパース
	picojson::array dataList = data["destList"].get<picojson::array>();

	//各データをそれぞれパース
	vector<int> destList;
	destList.resize(dataList.size());
	for (UINT i = 0; i < dataList.size(); i++)
	{
		destList[i] = static_cast<int>(dataList[i].get<picojson::object>()["dest"].get<double>());
	}

	//初期化
	model->Init(destList);

	return model;
}

/**************************************
ガイド生成処理
***************************************/
void SnakeEnemyFactory::CreateGuide(picojson::object & data, EnemyGuideArrowController * controller)
{
	//配列データをパース
	picojson::array dataList = data["destList"].get<picojson::array>();

	//各データをそれぞれパース
	vector<int> destList;
	destList.resize(dataList.size());
	for (UINT i = 0; i < dataList.size(); i++)
	{
		destList[i] = static_cast<int>(dataList[i].get<picojson::object>()["dest"].get<double>());
	}

	//destListからガイドの生成を予約
	for (UINT i = 0; i < destList.size() - 1; i++)
	{
		controller->Reserve(i * ENEMYGUIDEARROW_DURATION, LineTrailModel(destList[i], destList[i + 1]));
	}
}
