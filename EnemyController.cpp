//=====================================
//
//エネミーコントローラー処理[EnemyController.cpp]
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "EnemyController.h"
#include "TestEnemyModel.h"
#include "StopEnemyModel.h"

#include <algorithm>

using namespace std;

/**************************************
マクロ定義
***************************************/

/**************************************
構造体定義
***************************************/

/**************************************
グローバル変数
***************************************/

/**************************************
コンストラクタ
***************************************/
EnemyController::EnemyController()
{
	//ステートマシン作成
	fsm[EnemyType::Stop] = new StopEnemyModel();
}

/**************************************
デストラクタ
***************************************/
EnemyController::~EnemyController()
{
	//モデルコンテナクリア
	for (auto &model : modelContainer)
	{
		SAFE_DELETE(model);
	}
	modelContainer.clear();

	//ステートマシンクリア
	for (auto &state : fsm)
	{
		SAFE_DELETE(state.second);
	}
	fsm.clear();
}

/**************************************
初期化処理
***************************************/
void EnemyController::Init()
{
	cntFrame = 0;
}

/**************************************
終了処理
***************************************/
void EnemyController::Uninit()
{
	for (auto &model : modelContainer)
	{
		model->Uninit();
	}
}

/**************************************
更新処理
***************************************/
void EnemyController::Update()
{
	//エネミー生成処理
	//今は一旦、乱数で2秒おきにStopタイプを生成
	cntFrame++;
	if (cntFrame % 120 == 0)
	{
		int start, end;
		start = RandomRange(0, 5);
		end = WrapAround(0, 5, start + RandomRange(1, 5));
		SetEnemy(EnemyType::Stop, LineTrailModel(start, end));
	}

	//モデル更新処理
	for (auto &model : modelContainer)
	{
		model->Update();
	}
}

/**************************************
描画処理
***************************************/
void EnemyController::Draw()
{
	for (auto &model : modelContainer)
	{
		model->Draw();
	}
}

/**************************************
エネミー生成処理
***************************************/
void EnemyController::SetEnemy(EnemyType type, LineTrailModel trailModel)
{
	//未使用のEnemyModelを検索
	auto itr = find_if(modelContainer.begin(), modelContainer.end(), [](EnemyModel *model)
	{
		return !model->active;
	});

	//見つかったならソイツを使用
	if (itr != modelContainer.end())
	{
		(*itr)->Init(trailModel);
		(*itr)->ChangeState(fsm[type]);
	}
	//見つからなかったので新規作成
	else
	{
		EnemyModel *model = new EnemyModel();
		model->Init(trailModel);
		model->ChangeState(fsm[type]);
		modelContainer.push_back(model);
	}
	
}