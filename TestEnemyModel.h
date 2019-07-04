//=====================================
//
//テストエネミーモデルヘッダ[TestEnemyModel.h]
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _TESTENEMYMODEL_H_
#define _TESTENEMYMODEL_H_

#include "main.h"
#include "IStateMachine.h"
#include "EnemyModel.h"

/**************************************
マクロ定義
***************************************/

/**************************************
クラス定義
***************************************/
class TestEnemyModel : public IStateMachine<EnemyModel>
{
public:
	void OnStart(EnemyModel *entity);
	int OnUpdate(EnemyModel *entity);
	void OnExit(EnemyModel *entity);
};

#endif