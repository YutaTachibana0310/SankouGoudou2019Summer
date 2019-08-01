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
#include "LineTrailModel.h"

#include <array>
#include <list>

class EnemyGuideReserve;

/**************************************
マクロ定義
***************************************/
#define ENEMYGUIDEARROW_EMITTER_MAX		(10)

/**************************************
EnemyGuideArrowControllerクラス
***************************************/
class EnemyGuideArrowController
{
public:
	EnemyGuideArrowController();
	~EnemyGuideArrowController();

	void Update();
	void Draw();

	void SetEmitter(LineTrailModel model);
	void Reserve(int delay, LineTrailModel model);

private:
	std::array<EnemyGuideArrowEmitter*, ENEMYGUIDEARROW_EMITTER_MAX> emitterContainer;
	std::list<EnemyGuideReserve> reserveList;
};

/**************************************
EnemyGuideReserveクラス
***************************************/
class EnemyGuideReserve
{
public:
	EnemyGuideReserve(int delayFrame, LineTrailModel model)
	{
		this->cntFrame = delayFrame;
		this->model = model;
	}

	int cntFrame;
	LineTrailModel model;
};
#endif