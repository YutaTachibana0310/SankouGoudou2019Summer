//=====================================
//
//ストレートエネミーモデルヘッダ[StraightEnemyModel.h]
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _STRAIGHTENEMYMODEL_H_
#define _STRAIGHTENEMYMODEL_H_

#include "main.h"
#include "EnemyModel.h"

/**************************************
マクロ定義
***************************************/

/**************************************
クラス定義
***************************************/
class StraightEnemyModel : public EnemyModel
{
public:
	StraightEnemyModel();
	~StraightEnemyModel();

	void Init(LineTrailModel model, int enemyNum);
	int Update();

private:
	const float StartPosZ;
	const float DestPosZ;
};

#endif