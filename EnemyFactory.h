//=====================================
//
//エネミーファクトリーヘッダ[EnemyFactory.h]
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _ENEMYFACTORY_H_
#define _ENEMYFACTORY_H_

#include "main.h"
#include "EnemyModel.h"
#include "picojson\picojson.h"
#include "EnemyGuideArrowController.h"

/**************************************
マクロ定義
***************************************/

/**************************************
クラス定義
***************************************/
class EnemyFactory
{
public:
	EnemyFactory() {}
	~EnemyFactory() {}

	virtual EnemyModel* Create(picojson::object& data) = 0;
	virtual void CreateGuide(picojson::object& data, EnemyGuideArrowController* controller) = 0;
};

#endif