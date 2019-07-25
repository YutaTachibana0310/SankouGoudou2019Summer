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
#include "EnemyBullet.h"

#include "Framework\ResourceManager.h"
#include "picojson\picojson.h"
#include "debugWindow.h"

#include <algorithm>
#include <fstream>

using namespace std;

/**************************************
マクロ定義
***************************************/
#define USE_DEBUG_TESTENEMY (1)

#define ENEMY_NUM_OUTERLINE		(3)		//五角形の外周に生成するエネミーの数
#define ENEMY_NUM_INNNERLINE	(5)		//五角形の内側に生成するエネミーの数

/**************************************
構造体定義
***************************************/

/**************************************
グローバル変数
***************************************/
//五角形の外周を構成するLineModel
const vector<LineTrailModel> EnemyController::OuterLineModel = {
	LineTrailModel(0, 1),
	LineTrailModel(1, 2),
	LineTrailModel(2, 3),
	LineTrailModel(3, 4),
	LineTrailModel(4, 0)
};

/**************************************
コンストラクタ
***************************************/
EnemyController::EnemyController()
{
	//リソース読み込み
	//解放はシーン終了時にGame.cppで一括して開放する
	ResourceManager::Instance()->LoadMesh("Enemy", "data/MODEL/Enemy/drone.x");

	//バレットコントローラ作成
	bulletController = new EnemyBulletController();

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
	
	//バレットコントローラ削除
	SAFE_DELETE(bulletController);

	//ステージデータクリア
	stageModelList.clear();

	//テスト用エネミーをdeleteする
	SAFE_DELETE(test);
}

/**************************************
初期化処理
***************************************/
void EnemyController::Init()
{
	cntFrame = 0;

	//新しく作るEnemyの初期化テストはここに書く
#if USE_DEBUG_TESTENEMY
	
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

	bulletController->Uninit();

	//新しく作るEnemyの終了テストはここに書く
#if USE_DEBUG_TESTENEMY

#endif
}

/**************************************
更新処理
***************************************/
void EnemyController::Update()
{
	//新しく作るEnemyの更新テストはここに書く
#if USE_DEBUG_TESTENEMY
	BeginDebugWindow("Console");
	if (DebugButton("EnemyBullet"))
	{
		vector<D3DXVECTOR3> tmpVector;
		tmpVector.resize(5, D3DXVECTOR3(0.0f, 0.0f, 300.0f));
		bulletController->SetEnemyBullet(tmpVector, LineTrailModel(0, 1));
	}
	EndDebugWindow("Console");
#endif

	//モデル更新処理
	for (auto &model : modelList)
	{
		model->Update();
	}

	//バレット更新処理
	bulletController->Update();

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

	//バレット描画
	bulletController->Draw();

	//新しく作るEnemyの描画テストはここに書く
#if USE_DEBUG_TESTENEMY

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

		else if (stageModelList[i].type == "Snake")
			_SetEnemySnake(stageModelList[i].data);

		currentIndex++;
	}
}

/**************************************
エネミー生成処理（Changeタイプ）
***************************************/
void EnemyController::_SetEnemyChange(picojson::object& data)
{
	//インスタンス生成
	ChangeEnemyModel *model = new ChangeEnemyModel();

	//データをパース
	int start = static_cast<int>(data["start"].get<double>());
	int end = static_cast<int>(data["end"].get<double>());
	LineTrailModel lineModel = LineTrailModel(start, end);

	//生成するエネミーの数を決定(五角形の外周なら3体、それ以外は5体)
	auto itr = find(OuterLineModel.begin(), OuterLineModel.end(), lineModel);
	int enemyNum = itr != OuterLineModel.end() ? ENEMY_NUM_OUTERLINE : ENEMY_NUM_INNNERLINE;

	//初期化
	model->Init(lineModel, enemyNum);

	modelList.push_back(model);
}

/**************************************
エネミー生成処理（Straightタイプ）
***************************************/
void EnemyController::_SetEnemyStraight(picojson::object& data)
{
	//インスタンス生成
	StraightEnemyModel *model = new StraightEnemyModel();

	//データをパース
	int start = static_cast<int>(data["start"].get<double>());
	int end = static_cast<int>(data["end"].get<double>());
	LineTrailModel lineModel = LineTrailModel(start, end);

	//生成するエネミーの数を決定(五角形の外周なら3体、それ以外は5体)
	auto itr = find(OuterLineModel.begin(), OuterLineModel.end(), lineModel);
	int enemyNum = itr != OuterLineModel.end() ? ENEMY_NUM_OUTERLINE : ENEMY_NUM_INNNERLINE;

	//初期化
	model->Init(lineModel, enemyNum);

	modelList.push_back(model);
}

/**************************************
エネミー生成処理（Snakeタイプ）
***************************************/
void EnemyController::_SetEnemySnake(picojson::object& data)
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