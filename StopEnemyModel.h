//=====================================
//
//ストップエネミーモデルヘッダ[StopEnemyModel.h]
//一時停止するタイプのエネミーモデル
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _STOPENEMYMODEL_H_
#define _STOPENEMYMODEL_H_

#include "main.h"
#include "EnemyModel.h"

/**************************************
マクロ定義
***************************************/

/**************************************
クラス定義
***************************************/
class StopEnemyModel : public IStateMachine<EnemyModel>
{
public:
	void OnStart(EnemyModel *entity);
	int OnUpdate(EnemyModel *entity);
	void OnExit(EnemyModel *entity);
};

#endif