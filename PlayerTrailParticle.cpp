//=====================================
//
//プレイヤートレイルパーティクル処理[PlayerTrailParticle.cpp]
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "PlayerTrailParticle.h"

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
PlayerTrailParticle初期化処理
***************************************/
void PlayerTrailParticle::Init()
{
	const int LifeRange = 10;
	const int InitLife = 11;
	const float InitSpeed = 5.0f;
	const float SpeedRange = 3.0f;

	lifeFrame = InitLife + RandomRange(-LifeRange, LifeRange);
	cntFrame = 0;
	moveDir = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	speed = InitSpeed + RandomRangef(-SpeedRange, SpeedRange);
	active = true;
}

/**************************************
PlayerTrailParticle終了処理
***************************************/
void PlayerTrailParticle::Uninit()
{
	active = false;
}

/**************************************
PlayerTrailParticle更新処理
***************************************/
void PlayerTrailParticle::Update()
{
	cntFrame++;

	//移動
	transform.pos += moveDir * speed;
	
	//寿命判定
	if (cntFrame > lifeFrame)
	{
		active = false;
	}
}

/**************************************
PlayerTrailEmitter初期化処理
***************************************/
void PlayerTrailEmitter::Init()
{
	active = true;
}

/**************************************
PlayerTrailEmitter終了処理
***************************************/
void PlayerTrailEmitter::Uninit()
{
	parentPos = NULL;
	parentActive = NULL;
	active = false;
}

/**************************************
PlayerTrailEmitter更新処理
***************************************/
void PlayerTrailEmitter::Update()
{
	if (*parentActive == false)
	{
		Uninit();
		return;
	}

	prevPos = transform.pos;
	transform.pos = *parentPos;
}

/**************************************
PlayerTrailEmitterセット処理
***************************************/
void PlayerTrailEmitter::SetParent(D3DXVECTOR3 *pPos, bool *pActive)
{
	parentPos = pPos;
	parentActive = pActive;
}
