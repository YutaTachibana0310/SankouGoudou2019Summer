//=====================================
//
//ボスホーミングアタックヘッダ[BossHomingAttack.h]
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _BOSSHOMINGATTACK_H_
#define _BOSSHOMINGATTACK_H_

#include "main.h"
#include "BossEnemyModel.h"

/**************************************
前方宣言
***************************************/

/**************************************
マクロ・列挙子定義
***************************************/

/**************************************
クラス定義
***************************************/
class BossEnemyModel::BossHomingAttack : public IStateMachine<BossEnemyModel>
{
public:
	void OnStart(BossEnemyModel* entity);
	int OnUpdate(BossEnemyModel* entity);

private:
	int cntFrame;
};

#endif