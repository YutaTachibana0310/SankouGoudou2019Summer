//=====================================
//
//ボス鉄筋アタック処理[BossRebarAttack.cpp]
//Author:GP12A332 21 立花雄太
//
//=====================================
#include "BossRebarAttack.h"
#include "BossEnemyActor.h"

/**************************************
マクロ定義
***************************************/

/**************************************
入場処理
***************************************/
void BossEnemyModel::BossRebarAttack::OnStart(BossEnemyModel* entity)
{
	cntFrame = 0;

	//アニメーション遷移
	entity->actor->ChangeAnimation(BossEnemyActor::AnimID::Attack02);
}

/**************************************
更新処理
***************************************/
int BossEnemyModel::BossRebarAttack::OnUpdate(BossEnemyModel* entity)
{
	const int RebarSetTime = 60;
	const int RebarMoveDuration = 85;
	const int RebarAttackTime = 200;
	const int RebarThrowDuration = 180;
	const int FinishTime = 300;

	cntFrame++;

	int result = BossEnemyModel::State::RebarAttack;

	if (cntFrame == RebarSetTime)
	{
		entity->SetRebar();
	}

	if (cntFrame == RebarAttackTime)
	{
		entity->ThrowRebar();
	}

	if (cntFrame == FinishTime)
	{
		entity->cntAttack++;
		if (entity->cntAttack == 1)
		{
			result = BossEnemyModel::State::Idle;
		}
		else
		{
			OnStart(entity);
		}
	}

	return result;
}
