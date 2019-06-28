//=====================================
//
//トレイルコライダー処理[TrailCollider.cpp]
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "TrailCollider.h"
#include <algorithm>

using namespace std;

/**************************************
マクロ定義
***************************************/
#define TRAILCOLLIDER_HIT_LENGTH		(20.0f)

/**************************************
構造体定義
***************************************/

/**************************************
static変数
***************************************/
map<TrailColliderTag, list<TrailCollider*>> TrailCollider::checkDictionary;

/**************************************
衝突判定
***************************************/
bool TrailCollider::CheckCollision(TrailCollider *other)
{
	//始点と終点の一致判定
	if(this->model != other->model)
		return false;

	//Z距離判定
	float dist = fabsf(*posZ - *(other->posZ));

	if (dist < TRAILCOLLIDER_HIT_LENGTH)
	{
		//自身と相手の観測者に衝突を通知
		ObserveSubject::NotifyObservers();
		other->NotifyObservers();

		return true;
	}
	else
	{
		return false;
	}
	
}

/**************************************
コンストラクタ
***************************************/
TrailCollider::TrailCollider(TrailColliderTag tag)
{
	this->tag = tag;
}

/**************************************
デストラクタ
***************************************/
TrailCollider::~TrailCollider()
{
	list<TrailCollider*> *checkList = &checkDictionary[tag];
	auto itr = find(checkList->begin(), checkList->end(), this);
	if (itr != checkList->end())
	{
		checkList->erase(itr);
	}
}

/**************************************
トレイルインデックスセット処理
***************************************/
void TrailCollider::SetTrailIndex(LineTrailModel model)
{
	this->model = model;
}

/**************************************
Z座標ポインタセット処理
***************************************/
void TrailCollider::SetAddressZ(float* adrPosZ)
{
	this->posZ = adrPosZ;
}

/**************************************
衝突判定
***************************************/
void TrailCollider::UpdateCollision()
{
	//プレイヤーバレットとエネミーの衝突判定
	for (TrailCollider* bullet : checkDictionary[TrailColliderTag::PlayerBullet])
	{
		for (TrailCollider *enemy : checkDictionary[TrailColliderTag::Enemy])
		{
			bullet->CheckCollision(enemy);
		}
	}
}

/**************************************
チェックリスト登録処理
***************************************/
void TrailCollider::RegisterToCheckList()
{
	list<TrailCollider*> *checkList = &checkDictionary[tag];

	//多重登録判定
	auto itr = find(checkList->begin(), checkList->end(), this);
	if (itr != checkList->end())
		return;

	//登録
	checkList->push_back(this);
}

/**************************************
チェックリスト離脱処理
***************************************/
void TrailCollider::RemoveFromCheckList()
{
	list<TrailCollider*> *checkList = &checkDictionary[tag];

	//登録確認
	auto itr = find(checkList->begin(), checkList->end(), this);
	if (itr == checkList->end())
		return;

	//離脱
	checkList->erase(itr);
}