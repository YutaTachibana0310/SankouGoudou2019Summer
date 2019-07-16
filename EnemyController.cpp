//=====================================
//
//エネミーコントローラー処理[EnemyController.cpp]
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "EnemyController.h"
#include "TestEnemyModel.h"
#include "ChangeEnemyModel.h"
#include "StraightEnemyModel.h"
#include "SnakeEnemyModel.h"

#include "Framework\ResourceManager.h"
#include "picojson\picojson.h"

#include <algorithm>
#include <fstream>

using namespace std;

/**************************************
マクロ定義
***************************************/
#define USE_DEBUG_TESTENEMY (1)

/**************************************
構造体定義
***************************************/

/**************************************
グローバル変数
***************************************/
static SnakeEnemyModel *snakeModel;

/**************************************
コンストラクタ
***************************************/
EnemyController::EnemyController()
{
	//リソース読み込み
	//解放はシーン終了時にGame.cppで一括して開放する
	ResourceManager::Instance()->LoadMesh("Enemy", "data/MODEL/airplane000.x");

	//ステージデータ読み込み
	LoadStageData();
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

	//ステージデータクリア
	stageModelList.clear();

	//テスト用エネミーをdeleteする
	SAFE_DELETE(test);
	SAFE_DELETE(snakeModel);
}

/**************************************
初期化処理
***************************************/
void EnemyController::Init()
{
	cntFrame = 0;

	//新しく作るEnemyの初期化テストはここに書く
#if USE_DEBUG_TESTENEMY
	snakeModel = new SnakeEnemyModel();
	vector<int> testList;
	testList.push_back(3);
	testList.push_back(2);
	testList.push_back(4);
	testList.push_back(1);
	snakeModel->Init(testList);
#endif
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

	//新しく作るEnemyの終了テストはここに書く
#if USE_DEBUG_TESTENEMY
	snakeModel->Uninit();
#endif
}

/**************************************
更新処理
***************************************/
void EnemyController::Update()
{
	//新しく作るEnemyの更新テストはここに書く
#if USE_DEBUG_TESTENEMY
	snakeModel->Update();
#endif

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

	//新しく作るEnemyの描画テストはここに書く
#if USE_DEBUG_TESTENEMY
	snakeModel->Draw();
#endif
}

/**************************************
エネミー生成インターフェース
***************************************/
void EnemyController::SetEnemy()
{
	cntFrame++;

	//現在のインデックスからステージデータを確認していく
	for (UINT i = currentIndex; i < stageModelList.size(); i++)
	{
		//生成タイミング前であればbreak
		if (cntFrame < stageModelList[i].frame)
			break;

		//typeに応じて生成処理をディスパッチ
		if (stageModelList[i].type == "Change")
			_SetEnemyChange(stageModelList[i].data);
		
		else if (stageModelList[i].type == "Straight")
			_SetEnemyStraight(stageModelList[i].data);

		currentIndex++;
	}
}

/**************************************
エネミー生成処理（Changeタイプ）
***************************************/
void EnemyController::_SetEnemyChange(picojson::object& data)
{
	//インスタンス生成
	EnemyModel *model = new ChangeEnemyModel();

	//データをパース
	int start = static_cast<int>(data["start"].get<double>());
	int end = static_cast<int>(data["end"].get<double>());

	//初期化
	model->Init(LineTrailModel(start, end));

	modelList.push_back(model);
}

/**************************************
エネミー生成処理（Straightタイプ）
***************************************/
void EnemyController::_SetEnemyStraight(picojson::object& data)
{
	//インスタンス生成
	EnemyModel *model = new StraightEnemyModel();

	//データをパース
	int start = static_cast<int>(data["start"].get<double>());
	int end = static_cast<int>(data["end"].get<double>());

	//初期化
	model->Init(LineTrailModel(start, end));

	modelList.push_back(model);
}

/**************************************
ステージデータ読み込み処理
***************************************/
bool EnemyController::LoadStageData()
{
	//JSONファイルを開く
	ifstream ifs;
	ifs.open("data/JSON/test.json", std::ios::binary);

	//成功確認
	if (!ifs.is_open())
		return false;

	//JSONデータを読み込み
	picojson::value val;
	ifs >> val;
	ifs.close();

	//データ配列をパースする
	picojson::array& dataList = val.get<picojson::object>()["StageData"].get<picojson::array>();

	//データを1個1個パースしてStageModelを作成する
	stageModelList.resize(dataList.size());
	for (UINT i = 0; i < dataList.size(); i++)
	{
		int frame = static_cast<int>(dataList[i].get<picojson::object>()["frame"].get<double>());
		string type = dataList[i].get<picojson::object>()["type"].get<string>();
		picojson::object data = dataList[i].get<picojson::object>()["data"].get<picojson::object>();

		stageModelList[i] = StageModel(frame, type, data);
	}

	//インデックス初期化
	currentIndex = 0;

	return true;
}