//=====================================
//
//プレイヤーボンバーパーティクル処理[PlayerBomberParticle.cpp]
//Author:GP12B332 12 権頭
//
//=====================================
#include "PlayerBomberParticle.h"

/**************************************
マクロ定義
***************************************/
#define BOMBER_PARTICLE_ROT	(2.0f)

/**************************************
PlayerBomberParticle初期化処理
***************************************/
void PlayerBomberParticle::Init()
{
	active = true;
	cntFrame = 0;
	transform.scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
}

/**************************************
PlayerBomberParticle終了処理
***************************************/
void PlayerBomberParticle::Uninit()
{
	active = false;
}

/**************************************
PlayerBomberParticle更新処理
***************************************/
void PlayerBomberParticle::Update()
{
	//移動処理
	transform.pos += moveDir * speed;
	transform.rot.z += BOMBER_PARTICLE_ROT;
	//transform.scale.x -= 0.01f;
	//transform.scale.y -= 0.01f;

	//寿命判定
	cntFrame++;

	float t = (float)cntFrame /(float)lifeFrame;

	if (cntFrame > lifeFrame)
	{
		active = false;
	}
}

/**************************************
PlayerBomberParticleパラメータ設定
***************************************/
void PlayerBomberParticle::SetParameter(D3DXVECTOR3 *moveDir, int lifeFrame)
{
	this->moveDir = *moveDir;
	this->lifeFrame = lifeFrame;
}
/**************************************
PlayerBomberParticleEmitter初期化処理
***************************************/
void PlayerBomberParticleEmitter::Init()
{
	prevPos = transform.pos;
	active = true;
	cntFrame = 0;
}

/**************************************
PlayerBomberParticleEmitter終了処理
***************************************/
void PlayerBomberParticleEmitter::Uninit()
{
	parentActive = nullptr;
	parentPos = nullptr;
}

/**************************************
PlayerBomberParticleEmitter更新処理
***************************************/
void PlayerBomberParticleEmitter::Update()
{
	transform.pos = *parentPos;

	if (!*parentActive)
		active = false;
}

/**************************************
PlayerBomberParticleEmitterパラメータ設定
***************************************/
void PlayerBomberParticleEmitter::SetParameter(bool* pActive, D3DXVECTOR3 *pPos)
{
	this->parentActive = pActive;
	this->parentPos = pPos;
}


