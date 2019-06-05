//=====================================
//
//ベースパーティクル処理[BaseParticle.cpp]
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "BaseParticle.h"

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
セット処理
***************************************/
void BaseParticle::Set(D3DXVECTOR3 *setPos, int lifeFrame)
{
	pos = *setPos;
	cntFrame = 0;
	active = true;
	this->lifeFrame = lifeFrame;
}

/**************************************
移動パラメータセット処理
***************************************/
void BaseParticle::SetMoveParameter(D3DXVECTOR3 *moveDir, float speed, EasingType easeType)
{
	D3DXVec3Normalize(&this->moveDir, moveDir);
	this->speed = speed;
	this->easeType = easeType;
}

/**************************************
移動処理
***************************************/
void BaseParticle::Update()
{
	if (!active)
		return;

	//移動判定
	float t = (float)cntFrame / (float)lifeFrame;
	float curSpeed = Easing<float>::GetEasingValue(t, &speed, &EndSpeed, easeType);
	pos += moveDir * curSpeed;

	//寿命判定
	cntFrame++;
	if (cntFrame > lifeFrame)
		active = false;
}

/**************************************
アクティブ判定
***************************************/
bool BaseParticle::IsActive()
{
	return active;
}
