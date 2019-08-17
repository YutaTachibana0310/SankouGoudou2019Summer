//=====================================
//
//�{�X�G�l�~�[���f���w�b�_[BossEnemyModel.h]
//Author:GP12B332 21 ���ԗY��
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
�}�N����`
***************************************/
class BossEnemyActor;

/**************************************
�N���X��`
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

private:
	BossEnemyActor* actor;
	std::unordered_map < State, IStateMachine<BossEnemyModel>*> fsm;
	IStateMachine<BossEnemyModel>* state;
	State currentState, prevState;

	std::list<RebarObstacle*> rebarList;

	class BossInit;
	class BossRebarAttack;
	class BossHomingAttack;
	class BossIdle;
};

#endif