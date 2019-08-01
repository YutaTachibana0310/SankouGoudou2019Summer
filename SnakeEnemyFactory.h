//=====================================
//
//スネークエネミーファクトリーヘッダ[SnakeEnemyFactory.h]
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _SNAKEENEMYFACTORY_H_
#define _SNAKEENEMYFACTORY_H_

#include "main.h"
#include "EnemyFactory.h"

/**************************************
マクロ定義
***************************************/

/**************************************
クラス定義
***************************************/
class SnakeEnemyFactory : public EnemyFactory
{
public:
	SnakeEnemyFactory() {}
	~SnakeEnemyFactory() {}

	EnemyModel* Create(picojson::object& data) override;
	void CreateGuide(picojson::object& data, EnemyGuideArrowController* controller) override;
};

#endif