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
	const int AnimationChangeTiming = 10;
	const int FinishTiming = 240;

	cntFrame++;

	effect->pos = entity->actor->GetActorPosition();
	core->pos = entity->actor->GetActorPosition();

	if(cntFrame == AnimationChangeTiming)
		entity->actor->ChangeAnimation(BossEnemyActor::AnimID::Defeat);

	if (cntFrame == FinishTiming)
	{
		entity->isDestroyed = true;
		entity->Explode();
	}

	return BossEnemyModel::State::Defeat;
}
