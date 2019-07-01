//=====================================
//
//エネミーコントローラーヘッダ[EnemyController.h]
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _ENEMYCONTROLLER_H_
#define _ENEMYCONTROLLER_H_

#include "main.h"
#include "Framework\BaseObserver.h"
#include "EnemyModel.h"
#include "IStateMachine.h"
#include <vector>
#include <map>

/**************************************
列挙子定義
***************************************/
enum class EnemyType
{
	Test,
	Max
};

/**************************************
クラス定義
***************************************/
class EnemyController
{
public:
	EnemyController();
	~EnemyController();

	void Init();
	void Uninit();
	void Update();
	void Draw();

private:
	std::vector<EnemyModel*> modelContainer;
	std::map<EnemyType, IStateMachine<EnemyModel>*> fsm;
};

#endif