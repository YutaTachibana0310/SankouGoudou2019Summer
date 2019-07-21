//=====================================
//
//プレイヤートレイルパーティクルコントローラヘッダ[PlayerTrailParticleController.h]
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _PLAYERTRAILPARTICLECONTROLLER_H_
#define _PLAYERTRAILPARTICLECONTROLLER_H_

#include "main.h"
#include "Framework\BaseParticleController.h"

/**************************************
マクロ定義
***************************************/

/**************************************
クラス定義
***************************************/
class PlayerTrailParticleController : public BaseParticleController
{
public:
	void Init();
	void Emit();
	void SetEmitter(D3DXVECTOR3 *pPos, bool *pActive);
};

#endif