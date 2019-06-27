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

/**************************************
マクロ定義
***************************************/

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

	TrailCollider(const char* tag);
	~TrailCollider();

	bool CheckCollision(TrailCollider *other);
	void SetTrailIndex(LineTrailModel model);
	void SetAddressZ(float* adrPosZ);

	void RegisterToCheckList();
	void RemoveFromCheckList();

	static void UpdateCollision();

private:
	TrailCollider() {}

	LineTrailModel model;
	float *posZ;
	std::string tag;

	static std::map<std::string, std::list<TrailCollider*>> checkDictionary;
};


#endif