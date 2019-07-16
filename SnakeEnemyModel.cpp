//=====================================
//
//スネークエネミーモデル処理[SnakeEnemyModel.cpp]
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "SnakeEnemyModel.h"
#include "enemy.h"

using namespace std;

/**************************************
マクロ定義
***************************************/
typedef EnemyModel Base;

#define SNAKEENEMY_START_OFFSET		(400.0f)
#define SNAKEENEMY_MOVE_DURATION	(30.0f)

/**************************************
初期化処理
***************************************/
void SnakeEnemyModel::Init(vector<int> destList)
{

	collider->active = false;
	pos.z = 250.0f;

	//destListからモデルリストを作成
	vector<LineTrailModel> modelList;
	for (UINT i = 0; i < destList.size() - 1; i++)
	{
		modelList.push_back(LineTrailModel(destList[i], destList[i + 1]));
	}

	//モデルリストからコライダーリストを作成
	colliderList.resize(modelList.size());
	for (UINT i = 0; i < modelList.size(); i++)
	{
		colliderList[i] = new TrailCollider(TrailColliderTag::Enemy);
		colliderList[i]->SetTrailIndex(modelList[i]);
		colliderList[i]->SetAddressZ(&pos.z);
		colliderList[i]->AddObserver(this);
	}

	//移動座標リストを作成
	vector<D3DXVECTOR3> moveTargetList;
	moveTargetList.resize(destList.size() + 2);

	//destListから座標を取得して設定
	for (UINT i = 0; i < destList.size(); i++)
	{
		moveTargetList[i + 1] = LineTrailModel::GetEdgePos(destList[i]);
	}

	//初期座標を計算
	D3DXVECTOR3 initDiff = moveTargetList[1] - moveTargetList[2];
	D3DXVec3Normalize(&initDiff, &initDiff);
	moveTargetList[0] = moveTargetList[1] + initDiff * SNAKEENEMY_START_OFFSET;

	//最終座標を計算
	UINT lastIndex = moveTargetList.size() - 1;
	D3DXVECTOR3 lastDiff = moveTargetList[lastIndex - 1] - moveTargetList[lastIndex - 2];
	D3DXVec3Normalize(&lastDiff, &lastDiff);
	moveTargetList[lastIndex] = moveTargetList[lastIndex - 1] + lastDiff * SNAKEENEMY_START_OFFSET;

	//Z座標を設定
	for (auto& target : moveTargetList)
	{
		target.z = pos.z;
	}

	//移動時間リスト
	vector<float> timeList;
	timeList.resize(moveTargetList.size());
	for (auto& time : timeList)
	{
		time = SNAKEENEMY_MOVE_DURATION;
	}

	//エネミーを作成
	EnemySnake *snake = new EnemySnake;
	snake->VInit();
	snake->Set(moveTargetList, timeList, 60.0f);
	enemyList.push_back(snake);
}

/**************************************
更新処理
***************************************/
int SnakeEnemyModel::Update()
{
	for (auto& enemy : enemyList)
	{
		enemy->VUpdate();
	}

	return 0;
}

/**************************************
更新処理
***************************************/
void SnakeEnemyModel::Draw()
{
	for (auto& enemy : enemyList)
	{
		enemy->VDraw();
	}

	for (auto& collider : colliderList)
	{
		TrailCollider::DrawCollider(collider);
	}
}

/**************************************
衝突判定
***************************************/