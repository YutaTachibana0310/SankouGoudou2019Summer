//=====================================
//
//エネミーガイドアローコントローラヘッダ[EnemyGuideArrowController.h]
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _ENEMYGUIDEARROWCONTROLLER_H_
#define _ENEMYGUIDEARROWCONTROLLER_H_

#include "main.h"
#include "EnemyGuideArrow.h"

#include <array>

class LineTrailModel;
/**************************************
マクロ定義
***************************************/
#define ENEMYGUIDEARROW_EMITTER_MAX		(10)

/**************************************
クラス定義
***************************************/
class EnemyGuideArrowController
{
public:
	EnemyGuideArrowController();
	~EnemyGuideArrowController();

	void Update();
	void Draw();

	void SetEmitter(LineTrailModel model);

private:
	std::array<EnemyGuideArrowEmitter*, ENEMYGUIDEARROW_EMITTER_MAX> emitterContainer;
};

#endif