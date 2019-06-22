//=====================================
//
//スコアパーティクルコントローラヘッダ[ScoreParticleController.h]
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _SCOREPARTICLECONTROLLER_H_
#define _SCOREPARTICLECONTROLLER_H_

#include "main.h"
#include <vector>

#include "Framework\BaseParticleController.h"
#include "ScoreParticle.h"

/**************************************
マクロ定義
***************************************/

/**************************************
前方宣言
***************************************/
class ScoreParticle;
class ScoreParticleEmitter;

/**************************************
クラス定義
***************************************/
class ScoreParticleController : public BaseParticleController
{
public:
	void Init();
	void SetEmitter(D3DXVECTOR3 *pos);
	void Emit();
};
#endif