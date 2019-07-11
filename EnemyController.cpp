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
	fsm[EnemyModelType::Stop] = new StopEnemyModel();
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

	//エネミーコンテナクリア
	for (auto& enemyList : enemyContainer)
	{
		for (auto& enemy : enemyList.second)
		{
			SAFE_DELETE(enemy);
		}
		enemyList.second.clear();
	}
	enemyContainer.clear();
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

	for (auto& enemyList : enemyContainer)
	{
		for (auto& enemy : enemyList.second)
		{
			enemy->VUninit();
		}
	}
}

/**************************************
更新処理
***************************************/
void EnemyController::Update()
{
	//モデル更新処理
	for (auto &model : modelContainer)
	{
		model->Update();
	}

	//エネミー更新処理
	for (auto &enemyList : enemyContainer)
	{
		for (auto& enemy : enemyList.second)
		{
			enemy->VUpdate();
		}
	}
}

/**************************************
描画処理
***************************************/
void EnemyController::Draw()
{
	//エネミーモデル描画
	for (auto &model : modelContainer)
	{
		model->Draw();
	}

	//エネミー描画
	for (auto& enemyList : enemyContainer)
	{
		for (auto& enemy : enemyList.second)
		{
			enemy->VDraw();
		}
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
		_SetEnemy(EnemyModelType::Stop, LineTrailModel(start, end));
	}
}

/**************************************
エネミー生成処理（モデル版）
***************************************/
void EnemyController::_SetEnemy(EnemyModelType type, LineTrailModel trailModel)
{
	//未使用のEnemyModelを検索
	auto itr = find_if(modelContainer.begin(), modelContainer.end(), [](EnemyModel *model)
	{
		return !model->active;
	});

	//見つかったならソイツを使用
	EnemyModel *model = NULL;
	if (itr != modelContainer.end())
	{
		model = (*itr);
	}
	//見つからなかったので新規作成
	else
	{
		model = new EnemyModel();
		modelContainer.push_back(model);
	}

	//エネミーの実体を生成
	switch (type)
	{
	case EnemyModelType::Stop:
		_SetEnemyChange(model);
		break;
	}
	
	//初期化
	model->Init(trailModel);
	model->ChangeState(fsm[type]);
}

/**************************************
エネミー生成処理(実体版)
***************************************/
void EnemyController::_SetEnemyChange(EnemyModel* model)
{
	//TODO:セット数切り替えられるようにする
	UINT setNum = 5;
	UINT setCount = 0;
	const EnemyType Type = EnemyType::Change;

	//コンテナの中で未使用のエネミーを使用
	for (UINT i = 0; i < setNum; i++)
	{
		//未使用のエネミーを検索
		auto itr = find_if(enemyContainer[Type].begin(), enemyContainer[Type].end(), [](Enemy* enemy)
		{
			return !enemy->m_Active;
		});

		//いなかったのでbreak
		if (itr == enemyContainer[Type].end())
			break;

		//EnemyModelに追加
		model->AddEnemy((*itr));
		(*itr)->m_Active = true;
		setCount++;
	}

	//足りなかった分を新規作成
	for (UINT i = setCount; i < setNum; i++)
	{
		Enemy* newEnemy = new EnemyChange();

		//Enemyモデルに追加してコンテナ登録
		model->AddEnemy(newEnemy);
		enemyContainer[Type].push_back(newEnemy);
	}
}