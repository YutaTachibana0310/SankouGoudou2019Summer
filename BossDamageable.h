//=====================================
//
//ボスダメージエイブルヘッダ[BossDamageable.h]
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _BOSSDAMAGEABLE_H_
#define _BOSSDAMAGEABLE_H_

#include "main.h"
#include "BossEnemyModel.h"
#include "IStateMachine.h"

/**************************************
前方宣言
***************************************/

/**************************************
マクロ・列挙子定義
***************************************/

/**************************************
クラス定義
***************************************/
class BossEnemyModel::BossDamageable: public IStateMachine<BossEnemyModel>
{
public:
	void OnStart(BossEnemyModel *entity);
	int OnUpdate(BossEnemyModel *entity);

private:
	int cntFrame;
};

#endif