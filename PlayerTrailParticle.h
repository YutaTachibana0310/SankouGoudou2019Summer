//=====================================
//
//プレイヤートレイルパーティクルヘッダ[PlayerTrailParticle.h]
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _PLAYERTRAILPARTICLE_H_
#define _PLAYERTRAILPARTICLE_H_

#include "main.h"
#include "Framework\BaseParticle.h"
#include "Framework\BaseEmitter.h"

/**************************************
マクロ定義
***************************************/

/**************************************
PlayerTrailParticleクラス
***************************************/
class PlayerTrailParticle : public BaseParticle
{
public:
	void Init();
	void Uninit();
	void Update();

	D3DXVECTOR3 moveDir;
	float speed;
};

/**************************************
PlayerTrailEmitterクラス
***************************************/
class PlayerTrailEmitter : public BaseEmitter
{
public:
	void Init();
	void Uninit();
	void Update();
	void SetParent(D3DXVECTOR3 *pPos, bool *pActive);

	D3DXVECTOR3 prevPos;

private:
	D3DXVECTOR3 *parentPos;
	bool *parentActive;
	
};

#endif