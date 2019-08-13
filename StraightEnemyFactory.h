//=====================================
//
//ストレートエネミーファクトリーヘッダ[StraightEnemyFactory.h]
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _STRAIGHTENEMYFACTORY_H_
#define _STRAIGHTENEMYFACTORY_H_

#include "main.h"
#include "EnemyFactory.h"

/**************************************
マクロ定義
***************************************/

/**************************************
クラス定義
***************************************/
class StraightEnemyFactory : public EnemyFactory
{
public:
	StraightEnemyFactory() {}
	~StraightEnemyFactory() {}

	EnemyModel* Create(picojson::object& data);
	void CreateGuide(picojson::object& data, EnemyGuideArrowController* controller);
};


#endif