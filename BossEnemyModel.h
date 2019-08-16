//=====================================
//
//ボスエネミーモデルヘッダ[BossEnemyModel.h]
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _BOSSENEMYMODEL_H_
#define _BOSSENEMYMODEL_H_

#include "main.h"
#include "EnemyModel.h"

/**************************************
マクロ定義
***************************************/
class BossEnemyActor;

/**************************************
クラス定義
***************************************/
class BossEnemyModel : public EnemyModel
{
public:
	BossEnemyModel();
	~BossEnemyModel();

	int Update();
	void Draw();

private:
	BossEnemyActor* actor;
};

#endif