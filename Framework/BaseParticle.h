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

	virtual void Init() {};
	virtual void Uninit() {};
	virtual void Update() {};
	void EmbedTransform(Transform *pTransform);
	bool active;

	Transform transform;
	ParticleUV uv;
	int lifeFrame;

protected:
	int cntFrame;
};

#endif