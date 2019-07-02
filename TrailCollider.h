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

//#define TRAILCOLLIDER_USE_DEBUG

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

	static void UpdateCollision();

#ifdef TRAILCOLLIDER_USE_DEBUG
	static void DrawCollider(TrailCollider *collider);
#endif

private:
	TrailCollider() {}

	LineTrailModel model;
	float *posZ;
	TrailColliderTag tag;

	static std::map<TrailColliderTag, std::list<TrailCollider*>> checkDictionary;

	void RegisterToCheckList();
	void RemoveFromCheckList();
	
#ifdef TRAILCOLLIDER_USE_DEBUG
	static LineRenderer *renderer;
	static UINT instanceCount;
#endif
};


#endif