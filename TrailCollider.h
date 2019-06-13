//=====================================
//
//トレイルコライダーヘッダ[TrailCollider.h]
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _TRAILCOLLIDER_H_
#define _TRAILCOLLIDER_H_

#include "main.h"

/**************************************
マクロ定義
***************************************/

/**************************************
始点・終点定義
***************************************/
enum class TrailIndex
{
	Top,
	MiddleLeft,
	LowerLeft,
	LowerRight,
	MiddleRight,
	Max
};

/**************************************
トレイルコライダークラス
***************************************/
class TrailCollider
{
public:
	TrailCollider() {};
	~TrailCollider() {};

	bool CheckCollision(TrailCollider *other);
	void SetParam(TrailIndex start, TrailIndex end, float *adrPosZ);

private:
	TrailIndex start, end;
	float *posZ;
};


#endif