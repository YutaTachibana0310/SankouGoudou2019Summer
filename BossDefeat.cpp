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
	entity->ChargeExplode(effect, core);
}

/**************************************
グローバル変数
***************************************/
int BossEnemyModel::BossDefeat::OnUpdate(BossEnemyModel* entity)
{
	cntFrame++;

	effect->pos = entity->actor->GetActorPosition();
	core->pos = entity->actor->GetActorPosition();

	if(cntFrame == 10)
		entity->actor->ChangeAnimation(BossEnemyActor::AnimID::Defeat);

	if (cntFrame == 240)
	{
		entity->isDestroyed = true;
		entity->Explode();
	}

	return BossEnemyModel::State::Defeat;
}
