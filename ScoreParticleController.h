//=====================================
//
//スコアパーティクルコントローラヘッダ[ScoreParticleController.h]
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _SCOREPARTICLECONTROLLER_H_
#define _SCOREPARTICLECONTROLLER_H_

#include "main.h"

#include "Framework\BaseParticleController.h"

/**************************************
マクロ定義
***************************************/

/**************************************
クラス定義
***************************************/
class ScoreParticleController : public BaseParticleController
{
public:
	void Init();
	void Emit();
};
#endif