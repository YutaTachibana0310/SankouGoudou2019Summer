//=====================================
//
//ボスダメージエイブル処理[BossDamageable.cpp]
//Author:GP12A332 21 立花雄太
//
//=====================================
#include "BossDamageable.h"

/**************************************
マクロ定義
***************************************/

/**************************************
入場処理
***************************************/
void BossEnemyModel::BossDamageable::OnStart(BossEnemyModel* entity)
{
	cntFrame = 0;
	entity->SetCollider();
}

/**************************************
更新処理
***************************************/
int BossEnemyModel::BossDamageable::OnUpdate(BossEnemyModel* entity)
{
	cntFrame++;

	int result = BossEnemyModel::State::Damageable;

	if (cntFrame == 360)
	{
		result = BossEnemyModel::State::Idle;
		entity->colliderController->DeleteAll();
	}

	return result;
}
