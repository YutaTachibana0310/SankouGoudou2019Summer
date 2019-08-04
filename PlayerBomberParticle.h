//=====================================
//
//プレイヤーボンバーパーティクルヘッダ[PlayerBomberParticle.h]
//Author:GP12B332 12 権頭
//
//=====================================
#ifndef _PLAYERBOMBERPARTICLE_
#define _PLAYERBOMBERPARTICLE_

#include "main.h"
#include "Framework/AnimationParticle.h"
#include "Framework/BaseParticle.h"
#include "Framework/BaseEmitter.h"

/**************************************
マクロ定義
***************************************/

/**************************************
PlayerBomberParticleクラス定義
***************************************/
class PlayerBomberParticle : public BaseParticle
{
public:
	PlayerBomberParticle() {}
	~PlayerBomberParticle() {}

	void Init();
	void Uninit();
	void Update();
	void SetParameter(D3DXVECTOR3 *moveDir, int lifeFrame);
	
	D3DXVECTOR3 moveDir;
	float speed;
};

/**************************************
PlayerBomberParticleEmitterクラス定義
***************************************/
class PlayerBomberParticleEmitter : public BaseEmitter
{
public:
	PlayerBomberParticleEmitter() : BaseEmitter(){}

	void Init();
	void Uninit();
	void Update();
	void SetParameter(bool* pActive, D3DXVECTOR3 *pPos);

	bool*parentActive;
	D3DXVECTOR3 *parentPos;
	D3DXVECTOR3 prevPos;
};


#endif