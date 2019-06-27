//=====================================
//
//トレイルコライダーヘッダ[TrailCollider.h]
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _TRAILCOLLIDER_H_
#define _TRAILCOLLIDER_H_

#include "main.h"
#include "LineTrailModel.h"

/**************************************
マクロ定義
***************************************/

/**************************************
始点・終点定義
***************************************/

/**************************************
トレイルコライダークラス
***************************************/
class TrailCollider
{
public:
	friend class TrailCollider;

	TrailCollider() {};
	~TrailCollider() {};

	bool CheckCollision(TrailCollider *other);
	void SetTrailIndex(LineTrailModel model);
	void SetAddressZ(float* adrPosZ);

private:
	LineTrailModel model;
	float *posZ;
};


#endif