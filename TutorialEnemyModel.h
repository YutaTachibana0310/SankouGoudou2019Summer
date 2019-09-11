//=====================================
//
//TutorialEnemyModel.h
//機能:チュートリアルエネミーモデル
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _TUTORIALENEMYMODEL_H_
#define _TUTORIALENEMYMODEL_H_

#include "main.h"
#include "EnemyModel.h"

/**************************************
前方宣言
***************************************/

/**************************************
クラス定義
***************************************/
class TutorialEnemyModel : public EnemyModel
{
public:
	TutorialEnemyModel(LineTrailModel model, int enemyNum);

	int Update();
};
#endif