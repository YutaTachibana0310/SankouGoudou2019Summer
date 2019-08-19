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
#include "BossColliderController.h"

#include <unordered_map>
#include <list>

/**************************************
�}�N����`
***************************************/
class BossEnemyActor;
class EnemyBulletController;

/**************************************
�N���X��`
***************************************/
class BossEnemyModel
{
public:
	enum State
	{
		Init,
		RebarAttack,
		HomingAttack,
		Damageable,
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
	void FireBullet();

	void SetCollider();

private:
	BossEnemyActor* actor;
	std::unordered_map < State, IStateMachine<BossEnemyModel>*> fsm;
	IStateMachine<BossEnemyModel>* state;
	State currentState, prevState;

	std::list<RebarObstacle*> rebarList;

	EnemyBulletController *bulletController;

	BossColliderController *colliderController;

	int cntAttack;
	int updateResult;

	class BossInit;
	class BossRebarAttack;
	class BossHomingAttack;
	class BossIdle;
};

#endif