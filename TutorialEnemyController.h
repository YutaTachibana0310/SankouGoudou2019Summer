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
#include <memory>

/**************************************
前方宣言
***************************************/
class EnemyModel;
class Enemy;
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

	void GetEnemyList(std::list<std::shared_ptr<Enemy>>& out);

private:
	std::list<EnemyModel*> modelList;
};
#endif