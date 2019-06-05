//=====================================
//
//ベースパーティクルヘッダ[BaseParticle.h]
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _BASEPARTICLE_H_
#define _BASEPARTICLE_H_

#include "main.h"
#include "Framework\Easing.h"

/**************************************
マクロ定義
***************************************/

/**************************************
クラス定義
***************************************/
class BaseParticle
{
public:
	BaseParticle() {}
	virtual ~BaseParticle() {}

	void Set(D3DXVECTOR3 *setPos, int lifeFrame);
	void SetMoveParameter(D3DXVECTOR3 *moveDir, float speed, EasingType easeType = EasingType::None);
	void Update();
	bool IsActive();

	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	D3DXVECTOR3 scale;
	
private:
	const float EndSpeed = 0.0f;

	int lifeFrame;
	int cntFrame;
	bool active;

	float speed;
	D3DXVECTOR3 moveDir;
	EasingType easeType;
};


#endif