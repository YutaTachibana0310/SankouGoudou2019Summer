//=====================================
//
//プレイヤーボンバーパーティクル処理[PlayerBomberParticle.cpp]
//Author:GP12B332 12 権頭
//
//=====================================
#include "PlayerBomberParticle.h"
#include "Framework\Easing.h"

/**************************************
マクロ定義
***************************************/

/**************************************
PlayerBomber初期化処理
***************************************/
void PlayerBomberParticle::Init()
{
	active = true;
	cntFrame = 0;
	transform.scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
}

/**************************************
PlayerBomber終了処理
***************************************/
void PlayerBomberParticle::Uninit()
{
	active = false;
}

/**************************************
PlayerBomber更新処理
***************************************/
void PlayerBomberParticle::Update()
{
	//移動処理
	transform.pos += moveDir * speed;
	transform.rot.z += 2.0f;
	transform.scale.x -= 0.01f;
	transform.scale.y -= 0.01f;

	//寿命判定
	cntFrame++;
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
	//oldPos = *parentPos;
	transform.pos = *parentPos;

	//transform.pos - oldPos;

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


