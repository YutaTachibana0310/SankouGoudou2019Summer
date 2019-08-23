//=====================================
//
//ボス撃破処理[BossDefeat.cpp]
//Author:GP12A332 21 立花雄太
//
//=====================================
#include "BossDefeat.h"
#include "BossEnemyActor.h"

/**************************************
マクロ定義
***************************************/

/**************************************
クラス定義
***************************************/
void BossEnemyModel::BossDefeat::OnStart(BossEnemyModel* entity)
{
	cntFrame = 0;
	entity->Explode();
}

/**************************************
グローバル変数
***************************************/
int BossEnemyModel::BossDefeat::OnUpdate(BossEnemyModel* entity)
{
	cntFrame++;

	if(cntFrame == 10)
		entity->actor->ChangeAnimation(BossEnemyActor::AnimID::Defeat);

	return BossEnemyModel::State::Defeat;
}
