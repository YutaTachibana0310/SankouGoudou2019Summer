//=====================================
//
//ボス大ダメージヘッダ[BassLargeDamage.h]
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _BOSSLARGEDAMAGE_H_
#define _BOSSLARGEDAMAGE_H_

#include "main.h"
#include "IStateMachine.h"
#include "BossEnemyModel.h"

/**************************************
前方宣言
***************************************/
class BossEnemyModel;

/**************************************
マクロ・列挙子定義
***************************************/

/**************************************
クラス定義
***************************************/
class BossEnemyModel::BossLargeDamage : public IStateMachine<BossEnemyModel>
{
public:
	void OnStart(BossEnemyModel* entity);
	int OnUpdate(BossEnemyModel* entity);

private:
	int cntFrame;
};

#endif