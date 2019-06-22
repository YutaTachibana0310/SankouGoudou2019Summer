#pragma once
//=====================================
//
//プレイヤーバレットパーティクルヘッダ[PlayerBulletParticle.h]
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _PLAYERBULLETPARTICLE_H_
#define _PLAYERBULLETPARTICLE_H_

#include "main.h"
#include "Framework\BaseParticle.h"
#include "Framework\BaseEmitter.h"

/**************************************
マクロ定義
***************************************/

/**************************************
PlayerBulletParticleクラス定義
***************************************/
class PlayerBulletParticle : public BaseParticle
{
public:
	PlayerBulletParticle() {}
	~PlayerBulletParticle() {}

	void Init();
	void Uninit();
	void Update();
	void SetParameter(D3DXVECTOR3 *moveDir, int lifeFrame);

	D3DXVECTOR3 moveDir;
	float speed;
};

/**************************************
PlayerBulletParticleEmitterクラス定義
***************************************/
class PlayerBulletParticleEmitter : public BaseEmitter
{
public:
	PlayerBulletParticleEmitter() : BaseEmitter() {}

	void Init();
	void Uninit();
	void Update();
	void SetParameter(bool* pActive, D3DXVECTOR3 *pPos, D3DXVECTOR3 *pEdgeRight, D3DXVECTOR3 *pEdgeLeft);

	bool *parentActive;
	D3DXVECTOR3 *parentPos;
	D3DXVECTOR3 edgeRight, edgeLeft;
};

#endif