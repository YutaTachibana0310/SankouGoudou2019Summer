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
BaseParticleクラス
※継承先でInit(), Uninit(), Update()を実装する
***************************************/
class BaseParticle
{
public:
	BaseParticle();
	virtual ~BaseParticle();

	virtual void Init() = 0;
	virtual void Uninit() = 0;
	virtual void Update() = 0;
	void EmbedTransform(Transform *pTransform);
	bool active;

	Transform transform;
	ParticleUV uv;
	int lifeFrame;

protected:
	int cntFrame;
};

#endif