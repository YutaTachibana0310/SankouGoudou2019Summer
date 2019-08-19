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
#include "RebarOb.h"

#include <unordered_map>
#include <list>

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
		RebarAttack,
		HomingAttack,
		Idle
	};

	BossEnemyModel();
	~BossEnemyModel();

	int Update();
	void Draw();

	void ChangeState(State next);

	void SetRebar();
	void ThrowRebar();

	void StartBulletCharge();

private:
	BossEnemyActor* actor;
	std::unordered_map < State, IStateMachine<BossEnemyModel>*> fsm;
	IStateMachine<BossEnemyModel>* state;
	State currentState, prevState;

	std::list<RebarObstacle*> rebarList;

	int cntAttack;
	int updateResult;

	class BossInit;
	class BossRebarAttack;
	class BossHomingAttack;
	class BossIdle;
};

#endif