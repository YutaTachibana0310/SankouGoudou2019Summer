//=====================================
//
//スネークエネミーモデル処理[SnakeEnemyModel.cpp]
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "SnakeEnemyModel.h"
#include "enemy.h"
#include "GameParticleManager.h"
#include "ScoreManager.h"

#include <algorithm>

using namespace std;

/**************************************
マクロ定義
***************************************/
typedef EnemyModel Base;

#define SNAKEENEMY_START_OFFSET			(400.0f)		//エネミーの初期座標のオフセット
#define SNAKEENEMY_INIT_DURATION		(45.0f)			//最初のターゲットへ向かうのにかける時間-
#define SNAKEENEMY_MOVE_DURATION		(90.0f)			//エネミーが移動にかける時間
#define SNAKEENMY_GENERATE_NUM			(7)				//生成するエネミーの数
#define SNAKEENEMY_GENERATE_INTERVAL	(10)			//生成インターバル
#define SNAKEENEMY_GENERATE_DURATION	(SNAKEENMY_GENERATE_NUM*SNAKEENEMY_GENERATE_INTERVAL)

/**************************************
初期化処理
***************************************/
void SnakeEnemyModel::Init(vector<int> destList)
{
	active = true;
	cntFrame = 0;
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
		colliderList[i]->active = false;
	}

	//移動座標リストを作成
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

	//移動時間リスト作成
	timeList.resize(moveTargetList.size());
	for (UINT i = 0; i < moveTargetList.size(); i++)
	{
		float t = i == 0 || i == moveTargetList.size() - 1 ? SNAKEENEMY_INIT_DURATION : SNAKEENEMY_MOVE_DURATION;
		timeList[i] = t;
	}

	//最初のエネミーを生成
	shared_ptr<EnemySnake> enemy = make_shared<EnemySnake>();
	enemy->VInit();
	enemy->Set(moveTargetList, timeList, 60);
	enemyList.push_back(enemy);
}

/**************************************
更新処理
***************************************/
int SnakeEnemyModel::Update()
{
	//エネミーの生成
	if (++cntFrame < SNAKEENEMY_GENERATE_DURATION)
	{
		//インターバルおきに作成
		if (cntFrame % SNAKEENEMY_GENERATE_INTERVAL == 0)
		{
			shared_ptr<EnemySnake> enemy = make_shared<EnemySnake>();
			enemy->VInit();
			enemy->Set(moveTargetList, timeList, 60);
			enemyList.push_back(enemy);
		}
	}

	//エネミーの更新
	for (auto& enemy : enemyList)
	{
		enemy->VUpdate();
	}

	//当たり判定の更新
	for (auto& enemy : enemyList)
	{
		shared_ptr<EnemySnake> snake = dynamic_pointer_cast<EnemySnake>(enemy);

		UINT next = snake->m_CurrentIndex - 1;
		UINT current = snake->m_PrevIndex - 1;

		TrailCollider *nextCollider = next < colliderList.size() ? colliderList[next] : NULL;
		TrailCollider *currentCollider = current < colliderList.size() ? colliderList[current] : NULL;
		SwapInColliderMap(currentCollider, nextCollider, enemy);
	}

	//当たり判定を入れ替えたEnemyを元のリストから消去
	for (auto&& pair : colliderMap)
	{
		std::list<std::weak_ptr<Enemy>>& list = pair.second;

		//所属するコライダーのIDがちがうエネミーをリストから消去
		list.remove_if([&](std::weak_ptr<Enemy>& wptr)
		{
			std::shared_ptr<Enemy> sptr = wptr.lock();
			
			if (!sptr)
				return false;

			return dynamic_pointer_cast<EnemySnake>(sptr)->m_currentColliderID != pair.first;
		});

		//空になったコライダーを非アクティブ化
		if (list.empty())
		{
			auto itr = find_if(colliderList.begin(), colliderList.end(), [&](TrailCollider* collider)
			{
				return pair.first != collider->uniquID;
			});

			if (itr != colliderList.end())
				(*itr)->active = false;
		}
	}

	//終了判定
	if (cntFrame > SNAKEENEMY_GENERATE_DURATION)
	{
		//アクティブなエネミーが残っているか確認
		bool isActive = false;
		for (auto& enemy : enemyList)
		{
			isActive |= enemy->m_Active;
		}

		//残っていなければ終了
		if (!isActive)
			Uninit();
	}

	return 0;
}

/**************************************
衝突判定
***************************************/
void SnakeEnemyModel::OnNotified(ObserveSubject *notifier)
{
	TrailCollider *entity = static_cast<TrailCollider*>(notifier);

	//当たり判定に属するエネミーすべてにダメージ処理
	for (auto& enemy : colliderMap[entity->uniquID])
	{
		shared_ptr<Enemy> entity = enemy.lock();
		if (entity)
		{
			entity->m_FlgDestroyed = true;
		}
	}

	//所属エネミーリストをクリア
	colliderMap[entity->uniquID].clear();

	//衝突した当たり判定を非アクティブに
	entity->active = false;
}

/**************************************
当たり判定内入れ替え処理
***************************************/
void SnakeEnemyModel::SwapInColliderMap(TrailCollider* current, TrailCollider* next, std::shared_ptr<Enemy> enemy)
{
	//同じ判定へ入れ替えようとしていたら早期リターン
	if (current == next)
		return;

	//入れ替え元がNULLでなければ
	if(current != NULL)
	{
		//所属判定のエネミーリストの中から該当するエネミーを検索
		auto itr = find_if(colliderMap[current->uniquID].begin(), colliderMap[current->uniquID].end(), [&](weak_ptr<Enemy> ptr)
		{
			shared_ptr<Enemy> snake = ptr.lock();
			return enemy == snake;
		});

		/****** NOTE : for文の途中でeraseするとリストが壊れるのでここでは消去しない ****/
		////リストから離脱
		//colliderMap[current].erase(itr);

		////所属するエネミーがいなくなっていたら判定を非アクティブに
		//if (colliderMap[current].size() == 0)
		//	current->active = false;\

		//とりあえず所属コライダーのIDを変える
		dynamic_pointer_cast<EnemySnake>(enemy)->m_currentColliderID =  ~(dynamic_pointer_cast<EnemySnake>(enemy)->m_currentColliderID);
	}

	//入れ替え先がNULLであればreturn
	if (next == NULL)
		return;

	//入れ替え先のエネミーリストへプッシュ
	colliderMap[next->uniquID].push_back(enemy);

	//所属しているコライダーのIDを切り替える
	dynamic_pointer_cast<EnemySnake>(enemy)->m_currentColliderID = next->uniquID;

	//入れ替え先のコライダーをアクティベイト
	next->active = true;
}