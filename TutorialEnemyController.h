//=====================================
//
//TutorialEnemyController.h
//機能:チュートリアルエネミーコントローラ
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _TUTORIALENEMYCONTROLLER_H_
#define _TUTORIALENEMYCONTROLLER_H_

#include "main.h"
#include <list>
/**************************************
前方宣言
***************************************/
class EnemyModel;

/**************************************
クラス定義
***************************************/
class TutorialEnemyController
{
public:
	TutorialEnemyController();
	~TutorialEnemyController();

	void Update();
	void Draw();

	bool IsExistEnemy();

private:
	std::list<EnemyModel*> modelList;
};
#endif