//=====================================
//
//エネミーコントローラー処理[EnemyController.cpp]
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "EnemyController.h"
#include "TestEnemyModel.h"
#include "ChangeEnemyFactory.h"
#include "StraightEnemyFactory.h"
#include "SnakeEnemyFactory.h"
#include "EnemyBullet.h"
#include "GameParticleManager.h"

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

#define ENEMY_SHOTPOS_OFFSET	(D3DXVECTOR3(0.0f, 0.0f, -50.0f))
#define ENEMY_GUIDE_TIMING		(10)

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
	ResourceManager::Instance()->LoadMesh("Enemy", "data/MODEL/Enemy/drone.x");

	//各コントローラ作成
	bulletController = new EnemyBulletController();
	guideController = new EnemyGuideArrowController();

	//各ファクトリー作成
	factoryContainer["Change"] = new ChangeEnemyFactory();
	factoryContainer["Straight"] = new StraightEnemyFactory();
	factoryContainer["Snake"] = new SnakeEnemyFactory();

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
	
	//各コントローラ削除
	SAFE_DELETE(bulletController);
	SAFE_DELETE(guideController);

	//各ファクトリー削除
	for (auto& pair : factoryContainer)
	{
		SAFE_DELETE(pair.second);
	}
	factoryContainer.clear();

	//ステージデータクリア
	stageModelList.clear();
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

#endif

	//モデル更新処理
	for (auto &model : modelList)
	{
		int updateResult = model->Update();

		if (updateResult == AttackTiming)
			EnemyAttack(model);
		else if (updateResult == ChargeTiming)
			SetChageEffect(model);
	}

	//バレット更新処理
	bulletController->Update();

	//ガイド更新処理
	guideController->Update();

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
ガイド描画処理
***************************************/
void EnemyController::DrawGuide()
{
	guideController->Draw();
}

/**************************************
エネミー生成インターフェース
***************************************/
void EnemyController::SetEnemy()
{
	cntFrame++;

	//ガイド生成
	SetGuide();

	//現在のインデックスからステージデータを確認していく
	for (UINT i = currentIndex; i < stageModelList.size(); i++)
	{
		//生成タイミング前であればbreak
		if (cntFrame < stageModelList[i].frame)
			break;

		//typeに応じて生成処理をディスパッチ
		string type = stageModelList[i].type;
		EnemyModel* model = factoryContainer[type]->Create(stageModelList[i].data);
		modelList.push_back(model);

		currentIndex++;
	}
}

/**************************************
ガイド生成処理
***************************************/
void EnemyController::SetGuide()
{
	//現在のインデックスからデータを確認していく
	for (UINT i = currentIndex; i < stageModelList.size(); i++)
	{
		//ガイドタイミングでなければContinue
		if (cntFrame + ENEMY_GUIDE_TIMING != stageModelList[i].frame)
			continue;

		//ガイドタイミングより遅いデータが来たらbreak
		if (cntFrame + ENEMY_GUIDE_TIMING < stageModelList[i].frame)
			break;

		//ガイド生成
		string type = stageModelList[i].type;
		factoryContainer[type]->CreateGuide(stageModelList[i].data, guideController);
	}
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

/**************************************
エネミー攻撃処理
***************************************/
void EnemyController::EnemyAttack(EnemyModel *enermyModel)
{
	vector<D3DXVECTOR3> emitPos;
	emitPos.reserve(enermyModel->enemyList.size());

	for (auto& enemy : enermyModel->enemyList)
	{
		emitPos.push_back(enemy->m_Pos + ENEMY_SHOTPOS_OFFSET);
	}

	bulletController->SetEnemyBullet(emitPos, enermyModel->model);
}

/**************************************
エネミー攻撃チャージ開始処理
***************************************/
void EnemyController::SetChageEffect(EnemyModel *model)
{
	model->chageEffectList.clear();
	model->chageEffectList.resize(model->enemyList.size());

	UINT cntSet = 0;
	for (auto& enemey : model->enemyList)
	{
		BaseEmitter* emitter = GameParticleManager::Instance()->SetEnemyBulletCharge(&(enemey->m_Pos + ENEMY_SHOTPOS_OFFSET));
		model->chageEffectList[cntSet] = emitter;
		cntSet++;
	}
}

/**************************************
エネミー座標取得処理
***************************************/
void EnemyController::GetEnemyPositionList(vector<D3DXVECTOR3>& out)
{
	for (auto& model : modelList)
	{
		model->GetEnemyPosition(out);
	}
}

/**************************************
ボンバーシーケンスコールバック
***************************************/
void EnemyController::OnFinishBombSequence()
{
	bulletController->DisableAll();
}