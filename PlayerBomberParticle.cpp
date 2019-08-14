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
#define BOMBER_PARTICLE_ROT			(2.0f)
#define BOMBERTRAIL_LIFE_MIN		(15)
#define BOMBERTRAIL_LIFE_MAX		(25)
#define BOMBERTRAIL_SPEED_MAX		(2.0f)
#define BOMBERTRAIL_SPEED_MIN		(0.5f)

/**************************************
PlayerBomberParticle初期化処理
***************************************/
void PlayerBomberParticle::Init()
{
	active = true;
	cntFrame = 0;
	transform.Rotate(0.0f, 0.0f, RandomRangef(0.0f, 360.0f));
	transform.scale = RandomRangef(0.3f, 1.0f) * D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	speed = RandomRangef(BOMBERTRAIL_SPEED_MIN, BOMBERTRAIL_SPEED_MAX);
	lifeFrame = RandomRange(BOMBERTRAIL_LIFE_MIN, BOMBERTRAIL_LIFE_MAX);

	moveDir.x += RandomRangef(-0.1f, 0.1f);
	moveDir.y += RandomRangef(-0.1f, 0.1f);
}

/**************************************
PlayerBomberParticle更新処理
***************************************/
void PlayerBomberParticle::Update()
{
	//移動処理
	transform.pos += moveDir * speed;

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
void PlayerBomberParticle::SetMoveDir(const D3DXVECTOR3& moveDir)
{
	this->moveDir = moveDir;
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
	prevPos = transform.pos;
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


