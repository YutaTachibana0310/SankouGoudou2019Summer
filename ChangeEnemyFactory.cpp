//=====================================
//
//チェンジエネミーファクトリー処理[ChangeEnemyFactory.cpp]
//Author:GP12A332 21 立花雄太
//
//=====================================
#include "ChangeEnemyFactory.h"
#include "ChangeEnemyModel.h"

/**************************************
マクロ定義
***************************************/

/**************************************
エネミー生成処理
***************************************/
EnemyModel* ChangeEnemyFactory::Create(picojson::object& data)
{
	//インスタンス生成
	ChangeEnemyModel *model = new ChangeEnemyModel();

	//データをパース
	int start = static_cast<int>(data["start"].get<double>());
	int end = static_cast<int>(data["end"].get<double>());
	LineTrailModel lineModel = LineTrailModel(start, end);

	//生成するエネミーの数を決定(五角形の外周なら3体、それ以外は5体)
	auto itr = find(EnemyModel::OuterLineModel.begin(), EnemyModel::OuterLineModel.end(), lineModel);
	int enemyNum = itr != EnemyModel::OuterLineModel.end() ? ENEMY_NUM_OUTERLINE : ENEMY_NUM_INNNERLINE;

	//初期化
	model->Init(lineModel, enemyNum);

	return model;
}

/**************************************
ガイド生成処理
***************************************/
void ChangeEnemyFactory::CreateGuide(picojson::object& data, EnemyGuideArrowController* controller)
{
	//データをパース
	int start = static_cast<int>(data["start"].get<double>());
	int end = static_cast<int>(data["end"].get<double>());

	controller->SetEmitter(LineTrailModel(start, end));
}
