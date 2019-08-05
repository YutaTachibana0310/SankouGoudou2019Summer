//=====================================
//
//プレイヤーチャージパーティクルヘッダ[PlayerChargeParticle.h]
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _PLAYERCHARGEPARTICLE_H_
#define _PLAYERCHARGEPARTICLE_H_

#include "main.h"
#include "Framework\BaseParticle.h"
#include "Framework\BaseEmitter.h"

/**************************************
マクロ定義
***************************************/

/**************************************
PlayerChargeParticleクラス
***************************************/
class PlayerChargeParticle : public BaseParticle
{
public:
	void Init();
	void Update();

private:
	D3DXVECTOR3 moveDir;
	float speed;
};

/**************************************
PlayerChargeParticleEmitterクラス
***************************************/
class PlayerChargeParticleEmitter : public BaseEmitter
{
public:
	void Init();
	void Update();
};

#endif