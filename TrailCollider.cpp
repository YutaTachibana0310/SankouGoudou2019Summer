//=====================================
//
//トレイルコライダー処理[TrailCollider.cpp]
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "TrailCollider.h"

/**************************************
マクロ定義
***************************************/
#define TRAILCOLLIDER_HIT_LENGTH		(20.0f)

/**************************************
構造体定義
***************************************/

/**************************************
グローバル変数
***************************************/

/**************************************
衝突判定
***************************************/
bool TrailCollider::CheckCollision(TrailCollider *other)
{
	bool isHit;

	//始点と終点の一致判定

	if(this->model != other->model)
		return false;

	//Z距離判定
	float dist = fabsf(*posZ - *(other->posZ));

	return dist < TRAILCOLLIDER_HIT_LENGTH;
	
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