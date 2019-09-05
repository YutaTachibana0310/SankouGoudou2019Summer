//=====================================
//
//MidiumeEnemyFactory.cpp
//機能:中型エネミーを作成するファクトリクラス
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "MidiumEnemyFactory.h"
#include "MidiumEnemyModel.h"

/**************************************
グローバル変数
***************************************/

/**************************************
エネミー作成関数
***************************************/
EnemyModel * MidiumEnemyFactory::Create(picojson::object & data)
{
	//インスタンス生成
	MidiumEnemyModel *model = new MidiumEnemyModel();

	//配列データをパース
	picojson::array dataList = data["dataList"].get<picojson::array>();

	//各データをそれぞれパース
	vector<LineTrailModel> modelList;
	modelList.resize(dataList.size());
	for (UINT i = 0; i < dataList.size(); i++)
	{
		int start = static_cast<int>(dataList[i].get<picojson::object>()["start"].get<double>());
		int end = static_cast<int>(dataList[i].get < picojson::object>()["end"].get<double>());
		modelList.push_back(LineTrailModel(start, end));
	}

	//初期化
	model->Init(modelList);

	return model;
}

/**************************************
ガイド作成関数
***************************************/
void MidiumEnemyFactory::CreateGuide(picojson::object & data, EnemyGuideArrowController * container)
{
	//配列データをパース
	picojson::array dataList = data["dataList"].get<picojson::array>();

	//最初のラインにガイド生成
	int start = static_cast<int>(dataList[0].get<picojson::object>()["start"].get<double>());
	int end = static_cast<int>(dataList[0].get < picojson::object>()["end"].get<double>());
	container->SetEmitter(LineTrailModel(start, end));
}
