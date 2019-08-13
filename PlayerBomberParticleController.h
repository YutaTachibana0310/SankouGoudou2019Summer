//=====================================
//
//プレイヤーボンバーパーティクルコントローラヘッダ[PlayerBomberParticleController.h]
//Author:GP12B332 12　権頭
//
//=====================================
#ifndef _PLAYERBOMBERPARTICLECONTROLLER_H_
#define _PLAYERBOMBERPARTICLECONTROLLER_H_

#include "main.h"
#include "Framework/BaseParticleController.h"

/*******************************************
マクロ定義
********************************************/


/*******************************************
クラス定義
********************************************/
class PlayerBomberParticleController : public BaseParticleController
{
public:
	void Init();
	void Emit();
	void SetEmitter(D3DXVECTOR3 *pPos, bool *pActive);

};

#endif



