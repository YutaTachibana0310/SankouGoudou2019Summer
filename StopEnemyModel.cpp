//=====================================
//
//ストップエネミーモデル処理[StopEnemyModel.cpp]
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "StopEnemyModel.h"

/**************************************
マクロ定義
***************************************/
//初期化されてから当たり判定がアクティブになるタイミング
#define STOPENEMY_TIME_COLLIDER_ACTIVATE	(60)

//当たり判定が無効になるタイミング
#define STOPENEMT_TIME_ESCAPE				(300 + STOPENEMY_TIME_COLLIDER_ACTIVATE)

//終了タイミング
#define STOPENEMY_TIME_UNINIT				(60 + STOPENEMT_TIME_ESCAPE)

/**************************************
構造体定義
***************************************/

/**************************************
グローバル変数
***************************************/

/**************************************
入場処理
***************************************/
void StopEnemyModel::OnStart(EnemyModel *entity)
{
	entity->cntFrame = 0;

	//EnemyModelに属するEnemyに移動指示を出す
}

/**************************************
更新処理
***************************************/
int StopEnemyModel::OnUpdate(EnemyModel *entity)
{
	entity->cntFrame++;

	//60フレーム目で当たり判定をアクティブにする
	if (entity->cntFrame == STOPENEMY_TIME_COLLIDER_ACTIVATE)
		entity->collider->active = true;

	//アクティブになってから300フレームで離脱する
	if (entity->cntFrame == STOPENEMT_TIME_ESCAPE)
		entity->collider->active = false;

	//離脱開始してから60フレームで終了する
	if (entity->cntFrame == STOPENEMY_TIME_UNINIT)
		entity->Uninit();

	return StateContinuous;
}

/**************************************
退場処理
***************************************/
void StopEnemyModel::OnExit(EnemyModel *entity)
{

}