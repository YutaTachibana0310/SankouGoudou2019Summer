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

#include "Framework\ResourceManager.h"
#include "picojson\picojson.h"

#include <algorithm>
#include <fstream>

using namespace std;

/**************************************
マクロ定義
***************************************/
#define USE_DEBUG_TESTENEMY (0)

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
}

/**************************************
初期化処理
***************************************/
void EnemyController::Init()
{
	cntFrame = 0;

	//新しく作るEnemyの初期化テストはここに書く
#if USE_DEBUG_TESTENEMY
	//test
	test = new EnemySnake;
	std::vector<D3DXVECTOR3> posDestList;
	posDestList.push_back(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	posDestList.push_back(D3DXVECTOR3(50.0f, 0.0f, 0.0f));
	posDestList.push_back(D3DXVECTOR3(0.0f, 50.0f, 0.0f));
	posDestList.push_back(D3DXVECTOR3(0.0f, 0.0f, 50.0f));
	posDestList.push_back(D3DXVECTOR3(50.0f, 0.0f, 0.0f));
	posDestList.push_back(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	vector<float> frameDestList;
	frameDestList.push_back(50.0f);
	frameDestList.push_back(100.0f);
	frameDestList.push_back(200.0f);
	frameDestList.push_back(300.0f);
	frameDestList.push_back(400.0f);
	test->VInit();
	test->Set(posDestList, frameDestList, 50.0f);
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
	test->VUninit();
#endif
}

/**************************************
更新処理
***************************************/
void EnemyController::Update()
{
	//新しく作るEnemyの更新テストはここに書く
#if USE_DEBUG_TESTENEMY
	test->VUpdate();
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
	test->VDraw();
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

		if (stageModelList[i].type == "Change")
			_SetEnemyChange(stageModelList[i].data);

		currentIndex++;
	}
}

/**************************************
エネミー生成処理（モデル版）
***************************************/
void EnemyController::_SetEnemyChange(picojson::object& data)
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