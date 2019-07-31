//=====================================
//
//エネミーガイドアローコントローラヘッダ[EnemyGuideArrowController.h]
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _ENEMYGUIDEARROWCONTROLLER_H_
#define _ENEMYGUIDEARROWCONTROLLER_H_

#include "main.h"
#include "Framework\BaseParticleController.h"

class LineTrailModel;
/**************************************
マクロ定義
***************************************/

/**************************************
クラス定義
***************************************/
class EnemyGuideArrowController : public BaseParticleController
{
public:
	void Init();
	void Emit();

	void SetEmitter(LineTrailModel* model);
};

#endif