//=====================================
//
//テストエネミーモデル処理[TestEnemyModel.cpp]
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "TestEnemyModel.h"
#include "debugWindow.h"

/**************************************
マクロ定義
***************************************/

/**************************************
構造体定義
***************************************/

/**************************************
グローバル変数
***************************************/

/**************************************
入場処理
***************************************/
void TestEnemyModel::OnStart(EnemyModel *entity)
{
	entity->cntFrame = 0;
}

/**************************************
退場処理
***************************************/
void TestEnemyModel::OnExit(EnemyModel *entity)
{

}

/**************************************
更新処理
***************************************/
int TestEnemyModel::OnUpdate(EnemyModel *entity)
{
	entity->cntFrame++;

	//衝突判定リストに登録
	if(entity->cntFrame == 60)
	{
		entity->collider->RegisterToCheckList();
		return StateContinuous;
	}

	//攻撃
	if (entity->cntFrame == 120)
	{

		return AttackTiming;
	}

	//衝突判定リストから離脱
	if (entity->cntFrame == 180)
	{
		entity->collider->RemoveFromCheckList();
		entity->cntFrame = 0;
		return StateContinuous;
	}

	DebugLog("cnt:%d", entity->cntFrame);
}