//=====================================
//
//ボス初期状態処理[BossInit.cpp]
//Author:GP12A332 21 立花雄太
//
//=====================================
#include "BossInit.h"
#include "BossEnemyActor.h"
#include "Framework\Vector3.h"

/**************************************
マクロ定義
***************************************/
#define BOSSINIT_MOVE_DURATION		(180)
#define BOSSINIT_INITPOSITION		(D3DXVECTOR3(0.0f, 2000.0f, 1500.0f))
#define BOSSINIT_MOVE_POSITION		(D3DXVECTOR3(0.0f, -200.0f, 1500.0f))

/**************************************
入場処理
***************************************/
void BossEnemyModel::BossInit::OnStart(BossEnemyModel *entity)
{
	entity->actor->transform.pos = BOSSINIT_INITPOSITION;
	entity->actor->Move(BOSSINIT_MOVE_POSITION, BOSSINIT_MOVE_DURATION);

	entity->actor->ChangeAnimation(BossEnemyActor::AnimID::Flying);

	cntFrame = 0;
}

/**************************************
更新処理
***************************************/
int BossEnemyModel::BossInit::OnUpdate(BossEnemyModel *entity)
{
	cntFrame++;

	int result = BossEnemyModel::Init;
	if (cntFrame == BOSSINIT_MOVE_DURATION)
	{
		entity->actor->ChangeAnimation(BossEnemyActor::AnimID::Idle);
		result = BossEnemyModel::State::Damageable;
	}

	return result;
}
