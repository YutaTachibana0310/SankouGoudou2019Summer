//=====================================
//
//MidiumEnemyFactory.h
//機能:中型エネミーを作成するファクトリクラス
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _MIDIUMENEMYFACTORY_H_
#define _MIDIUMENEMYFACTORY_H_

#include "main.h"
#include "EnemyFactory.h"

/**************************************
前方宣言
***************************************/

/**************************************
クラス定義
***************************************/
class MidiumEnemyFactory : public EnemyFactory
{
	using EnemyFactory::EnemyFactory;
public:
	EnemyModel * Create(picojson::object& data);
	void CreateGuide(picojson::object & data, EnemyGuideArrowController* container);
};
#endif