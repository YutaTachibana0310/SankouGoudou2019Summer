//=====================================
//
//トレイルコライダーヘッダ[TrailCollider.h]
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _TRAILCOLLIDER_H_
#define _TRAILCOLLIDER_H_

#include "main.h"
#include "Framework\ObserveSubject.h"
#include "LineTrailModel.h"
#include <list>
#include <map>
#include <string>

#define TRAILCOLLIDER_USE_DEBUG

#ifdef TRAILCOLLIDER_USE_DEBUG
#include "LineRenderer.h"
#endif

/**************************************
TrailColliderTag列挙子
***************************************/
enum class TrailColliderTag
{
	PlayerBullet,
	Enemy,
	EnemyBullet,
	Player,
	Max
};

/**************************************
始点・終点定義
***************************************/

/**************************************
トレイルコライダークラス
***************************************/
class TrailCollider : public ObserveSubject
{
public:
	friend class TrailCollider;

	TrailCollider(TrailColliderTag tag);
	~TrailCollider();

	bool CheckCollision(TrailCollider *other);
	void SetTrailIndex(LineTrailModel model);
	void SetAddressZ(float* adrPosZ);

	bool active;
	UINT uniquID;

	static void UpdateCollision();

	static void DrawCollider(TrailCollider *collider);

private:
	TrailCollider() {}

	LineTrailModel model;
	float *posZ;
	TrailColliderTag tag;

	static std::map<TrailColliderTag, std::list<TrailCollider*>> checkDictionary;

	void RegisterToCheckList();
	void RemoveFromCheckList();
	
	static UINT instanceCount;
#ifdef TRAILCOLLIDER_USE_DEBUG
	static LineRenderer *renderer;
#endif
};


#endif