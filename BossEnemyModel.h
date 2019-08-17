//=====================================
//
//ボスエネミーモデルヘッダ[BossEnemyModel.h]
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _BOSSENEMYMODEL_H_
#define _BOSSENEMYMODEL_H_

#include "main.h"
#include "EnemyModel.h"
#include "IStateMachine.h"
#include <unordered_map>

/**************************************
マクロ定義
***************************************/
class BossEnemyActor;

/**************************************
クラス定義
***************************************/
class BossEnemyModel : public EnemyModel
{
public:
	enum State
	{
		Init,
		RaborAttack,
		HomingAttack,
		Idle
	};

	BossEnemyModel();
	~BossEnemyModel();

	int Update();
	void Draw();

	void ChangeState(State next);

private:
	BossEnemyActor* actor;
	std::unordered_map < State, IStateMachine<BossEnemyModel>*> fsm;
	IStateMachine<BossEnemyModel>* state;
	State currentState, prevState;

	class BossInit;
	class BossRaborAttack;
	class BossHomingAttack;
	class BossIdle;
};

#endif