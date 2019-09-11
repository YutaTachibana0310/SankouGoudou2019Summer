//=====================================
//
//TutorialEnemyController.cpp
//機能:チュートリアルエネミーコントローラ
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "TutorialEnemyController.h"
#include "Framework\ResourceManager.h"
#include "TutorialEnemyModel.h"
#include "LineTrailModel.h"

/**************************************
グローバル変数
***************************************/

/**************************************
コンストラクタ
***************************************/
TutorialEnemyController::TutorialEnemyController()
{
	ResourceManager::Instance()->LoadMesh("Enemy", "data/MODEL/Enemy/drone.x");
}

/**************************************
デストラクタ
***************************************/
TutorialEnemyController::~TutorialEnemyController()
{
	for (auto&& model : modelList)
	{
		SAFE_DELETE(model);
	}
	modelList.clear();
}

/**************************************
更新処理
***************************************/
void TutorialEnemyController::Update()
{
	//リストが空だったらエネミー追加
	if (modelList.empty())
	{
		int start = RandomRange(0, 5);
		int end = WrapAround(0, 5, start + RandomRange(1, 5));
		LineTrailModel model = LineTrailModel(start, end);
		modelList.push_back(new TutorialEnemyModel(model, 3));
	}

	for (auto&& model : modelList)
	{
		model->Update();
	}

	for (auto&& model : modelList)
	{
		model->CheckDestroied();
		if (!model->active)
			SAFE_DELETE(model);
	}

	modelList.remove_if([](EnemyModel* model)
	{
		return model == nullptr;
	});
}

/**************************************
描画処理
***************************************/
void TutorialEnemyController::Draw()
{
	for (auto&& model : modelList)
	{
		model->Draw();
	}
}

/**************************************
エネミー存在確認
***************************************/
bool TutorialEnemyController::IsExistEnemy()
{
	return !modelList.empty();
}

/**************************************
エネミー取得処理
***************************************/
void TutorialEnemyController::GetEnemyList(std::list<std::shared_ptr<Enemy>>& out)
{
	for (auto&& model : modelList)
	{
		model->GetEnemy(out);
	}
}
