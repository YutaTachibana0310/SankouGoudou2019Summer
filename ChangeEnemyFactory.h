//=====================================
//
//チェンジエネミーファクトリーヘッダ[ChangeEnemyFactory.h]
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _CHANGEENEMYFACTORY_H_
#define _CHANGEENEMYFACTORY_H_

#include "main.h"
#include "EnemyFactory.h"

/**************************************
マクロ定義
***************************************/

/**************************************
クラス定義
***************************************/
class ChangeEnemyFactory : public EnemyFactory
{
public:
	ChangeEnemyFactory() {}
	~ChangeEnemyFactory() {}

	EnemyModel* Create(picojson::object& data);
	void CreateGuide(picojson::object& data, EnemyGuideArrowController* controller);
};

#endif