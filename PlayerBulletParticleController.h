//=====================================
//
//プレイヤーバレットパーティクルコントローラヘッダ[PlayerBulletParticleController.h]
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _PLAYERBULLETPARTICLECONTROLLER_H_
#define _PLAYERBULLETPARTICLECONTROLLER_H_

#include "main.h"
#include "Framework\BaseParticleController.h"

/**************************************
マクロ定義
***************************************/

/**************************************
クラス定義
***************************************/
class PlayerBulletParticleController : public BaseParticleController
{
public:
	void Init();
	void Emit();
	void SetEmitter(D3DXVECTOR3 *pPos, bool *pActive, D3DXVECTOR3 *edgeRight, D3DXVECTOR3 *edgeLeft);
};

#endif