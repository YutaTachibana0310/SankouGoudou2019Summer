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

	if (entity->cntFrame < 60)
	{
		DebugLog("EnemyModel is stand by");
	}
	else if (entity->cntFrame < 120)
	{
		DebugLog("EnemyModel is Attack");
	}
	else
	{
		DebugLog("EnemyModel is Escape");
	}

	if (entity->cntFrame == 180)
		entity->cntFrame = 0;

	return StateContinuous;
}