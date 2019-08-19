//=====================================
//
//ボスホーミングアタック処理[BossHomingAttack.cpp]
//Author:GP12A332 21 立花雄太
//
//=====================================
#include "BossHomingAttack.h"
#include "BossEnemyActor.h"

/**************************************
マクロ定義
***************************************/

/**************************************
入場処理
***************************************/
void BossEnemyModel::BossHomingAttack::OnStart(BossEnemyModel *entity)
{
	cntFrame = 0;

	//アニメーション遷移
	entity->actor->ChangeAnimation(BossEnemyActor::AnimID::Attack01);

	//バレットチャージ開始
	entity->StartBulletCharge();
}

/**************************************
更新処理
***************************************/
int BossEnemyModel::BossHomingAttack::OnUpdate(BossEnemyModel* entity)
{
	return BossEnemyModel::State::HomingAttack;
}
