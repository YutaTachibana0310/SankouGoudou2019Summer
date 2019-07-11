//=====================================
//
//プレイヤーバレットパーティクル処理[PlayerBulletParticle.cpp]
//Author:GP12A332 21 立花雄太
//
//=====================================
#include "PlayerBulletParticle.h"
#include "Framework\Easing.h"

/**************************************
マクロ定義
***************************************/

/**************************************
PlayerBullet初期化処理
***************************************/
void PlayerBulletParticle::Init()
{
	active = true;
	cntFrame = 0;
	transform.scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	transform.scale.x += fabsf(moveDir.x)* 10.0f;
	transform.scale.y += fabsf(moveDir.y)* 10.0f;
}

/**************************************
PlayerBullet終了処理
***************************************/
void PlayerBulletParticle::Uninit()
{
	active = false;
}

/**************************************
PlayerBullet更新処理
***************************************/
void PlayerBulletParticle::Update()
{
	//移動処理
	transform.pos += moveDir * speed;

	//寿命判定
	cntFrame++;
	if (cntFrame > lifeFrame)
	{
		active = false;
	}
}

/**************************************
PlayerBulletParticleパラメータ設定
***************************************/
void PlayerBulletParticle::SetParameter(D3DXVECTOR3 *moveDir, int lifeFrame)
{
	this->moveDir = *moveDir;
	this->lifeFrame = lifeFrame;
}

/**************************************
PlayerBulletParticleEmitter初期化処理
***************************************/
void PlayerBulletParticleEmitter::Init()
{
	active = true;
	cntFrame = 0;
}

/**************************************
PlayerBulletParticleEmitter終了処理
***************************************/
void PlayerBulletParticleEmitter::Uninit()
{
	parentActive = nullptr;
	parentPos = nullptr;
}

/**************************************
PlayerBulletParticleEmitter更新処理
***************************************/
void PlayerBulletParticleEmitter::Update()
{
	transform.pos = *parentPos;

	if (!*parentActive)
		active = false;
}

/**************************************
PlayerBulletParticleEmitterパラメータ設定
***************************************/
void PlayerBulletParticleEmitter::SetParameter(bool* pActive, D3DXVECTOR3 *pPos, D3DXVECTOR3 *pEdgeRight, D3DXVECTOR3 *pEdgeLeft)
{
	this->parentActive = pActive;
	this->parentPos = pPos;
	this->edgeLeft = *pEdgeLeft;
	this->edgeRight = *pEdgeRight;
}