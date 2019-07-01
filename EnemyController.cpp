//=====================================
//
//エネミーコントローラー処理[EnemyController.cpp]
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "EnemyController.h"
#include "TestEnemyModel.h"

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
	fsm[EnemyType::Test] = new TestEnemyModel();
}

/**************************************
デストラクタ
***************************************/
EnemyController::~EnemyController()
{
	for (auto &model : modelContainer)
	{
		SAFE_DELETE(model);
	}
}

/**************************************
初期化処理
***************************************/
void EnemyController::Init()
{
	modelContainer.push_back(new EnemyModel());
	modelContainer[0]->ChangeState(fsm[EnemyType::Test]);
	modelContainer[0]->Init(LineTrailModel(0, 1));
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