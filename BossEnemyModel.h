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
#include <memory>

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
		LargeDamage,
		Idle,
		Defeat
	};

	BossEnemyModel(const Transform& player);
	~BossEnemyModel();

	int Update();
	void Draw();

	void ChangeState(State next);

	void SetRebar();
	void ThrowRebar();

	void StartBulletCharge();
	void FireBullet();

	void SetCollider();

	void OnDamage();

	void Explode();
	void ChargeExplode(Transform*& charge, Transform*& core);

private:
	BossEnemyActor* actor;
	std::unordered_map < State, IStateMachine<BossEnemyModel>*> fsm;
	IStateMachine<BossEnemyModel>* state;
	State currentState, prevState;

	std::list<std::unique_ptr<RebarObstacle>> rebarList;

	EnemyBulletController *bulletController;

	BossColliderController *colliderController;

	const Transform& player;

	int cntAttack;
	int level;
	
	class BossInit;
	class BossRebarAttack;
	class BossHomingAttack;
	class BossIdle;
	class BossLargeDamage;
	class BossDefeat;
};

#endif