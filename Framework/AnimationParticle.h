//=====================================
//
//アニメーションパーティクルヘッダ[AnimationParticle.h]
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _ANIMATIONPARTICLE_H_
#define _ANIMATIONPARTICLE_H_

#include "../main.h"
#include "BaseParticle.h"

/**************************************
マクロ定義
***************************************/

/**************************************
AnimationParticleクラス
***************************************/
class AnimationParticle : public BaseParticle
{
public:
	void SetAnimParameter(float texDixX, float texDivY);
	void SetAnimParameter(D3DXVECTOR2* texDiv);

protected:
	void Animation(float t);

	int animIndexMax;
	D3DXVECTOR2 texDiv;
	D3DXVECTOR2 texSize;
};
#endif