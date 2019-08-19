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
void BossDamageable::OnStart(BossEnemyModel* entity)
{
	cntFrame = 0;
	entity->SetCollider();
}

/**************************************
更新処理
***************************************/
int BossDamageable::OnUpdate(BossEnemyModel* entity)
{
	return 0;
}
