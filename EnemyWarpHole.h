//=====================================
//
//エネミーワープホールヘッダ[EnemyWarpHole.h]
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _ENEMYWARPHOLE_H_
#define _ENEMYWARPHOLE_H_

#include "main.h"
#include "Framework\AnimationParticle.h"
#include "Framework\BaseEmitter.h"

/**************************************
マクロ定義
***************************************/

/**************************************
EnemyWarpHoleクラス
***************************************/
class EnemyWarpHole : public AnimationParticle
{
public:
	EnemyWarpHole();
	~EnemyWarpHole();

	void Init();
	void Update();
};

/**************************************
EnemyWarpHoleEmitterクラス
***************************************/
class EnemyWarpHoleEmitter : public BaseEmitter
{
public:
	EnemyWarpHoleEmitter();
	~EnemyWarpHoleEmitter();

	void Init();
	void Update();
};

#endif