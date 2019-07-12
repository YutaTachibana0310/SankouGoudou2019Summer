//=====================================
//
//エネミーコントローラー処理[EnemyController.cpp]
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "EnemyController.h"
#include "TestEnemyModel.h"
#include "ChangeEnemyModel.h"

#include <algorithm>
#include "Framework\ResourceManager.h"

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
	//リソース読み込み
	//解放はシーン終了時にGame.cppで一括して開放する
	ResourceManager::Instance()->LoadMesh("Enemy", "data/MODEL/airplane000.x");
}

/**************************************
デストラクタ
***************************************/
EnemyController::~EnemyController()
{
	//モデルコンテナクリア
	for (auto &model : modelList)
	{
		SAFE_DELETE(model);
	}
	modelList.clear();
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
	for (auto &model : modelList)
	{
		model->Uninit();
	}
}

/**************************************
更新処理
***************************************/
void EnemyController::Update()
{
	//モデル更新処理
	for (auto &model : modelList)
	{
		model->Update();
	}

	//終了したモデルを削除する
	for (auto& model : modelList)
	{
		if (!model->active)
			SAFE_DELETE(model);
	}

	//削除したモデルをリストから削除
	modelList.remove_if([](EnemyModel* model)
	{
		return model == nullptr;
	});
}

/**************************************
描画処理
***************************************/
void EnemyController::Draw()
{
	//エネミーモデル描画
	for (auto &model : modelList)
	{
		model->Draw();
	}
}

/**************************************
エネミー生成インターフェース
***************************************/
void EnemyController::SetEnemy()
{
	//今は一旦、乱数で2秒おきにStopタイプを生成
	cntFrame++;
	if (cntFrame % 120 == 0)
	{
		int start, end;
		start = RandomRange(0, 5);
		end = WrapAround(0, 5, start + RandomRange(1, 5));
		_SetEnemy(string("Change"), LineTrailModel(start, end));
	}
}

/**************************************
エネミー生成処理（モデル版）
***************************************/
void EnemyController::_SetEnemy(string type, LineTrailModel trailModel)
{
	EnemyModel *model = nullptr;
	if (type == "Change")
		model = new ChangeEnemyModel();

	if (model == nullptr)
		return;

	//初期化
	model->Init(trailModel);

	modelList.push_back(model);
}