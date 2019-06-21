//=====================================
//
//ベースパーティクルヘッダ[BaseParticle.h]
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _BASEPARTICLE_H_
#define _BASEPARTICLE_H_

#include "../main.h"

/**************************************
マクロ定義
***************************************/

/**************************************
クラス定義
***************************************/
class BaseParticle
{
public:
	BaseParticle();
	virtual ~BaseParticle();

	virtual void Init() = 0;
	virtual void Uninit() = 0;
	virtual void Update() = 0;
	bool IsActive();

	Transform transform;
	ParticleUV uv;

protected:
	bool active;
	int cntFrame;
	int lifeFrame;
};

#endif