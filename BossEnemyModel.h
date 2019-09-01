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
#include "BossColliderController.h"

#include <unordered_map>
#include <list>
#include <memory>

/**************************************
マクロ定義
***************************************/
class BossEnemyActor;
class EnemyBulletController;
class BossUImanager;

/**************************************
クラス定義
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

	BossEnemyModel(const Transform& player, BossUImanager& uiManager);
	~BossEnemyModel();

	int Update();
	void Draw();

	void ChangeState(State next);

	void SetRebar();
	void ThrowRebar();

	void StartBulletCharge();
	void NotifyBullet();
	void FireBullet();

	void SetCollider();

	void OnDamage();

	void Explode();
	void ChargeExplode(Transform*& charge, Transform*& core);

	bool IsDesteoyed();

private:
	BossEnemyActor* actor;
	std::unordered_map < State, IStateMachine<BossEnemyModel>*> fsm;
	IStateMachine<BossEnemyModel>* state;
	State currentState, prevState;

	std::list<std::unique_ptr<RebarObstacle>> rebarList;

	EnemyBulletController *bulletController;
	std::vector<LineTrailModel> bulletReserve;

	BossColliderController *colliderController;

	const Transform& player;
	BossUImanager& uiManager;

	int cntAttack;
	int level;
	int cntLoop;
	bool isDestroyed;

	void MakeOneStrokeEdge(int edgeNum, std::vector<int>& edgeList);
	
	class BossInit;
	class BossRebarAttack;
	class BossHomingAttack;
	class BossIdle;
	class BossLargeDamage;
	class BossDefeat;
	class BossIdle;
	class BossDamageable;

	enum Const
	{
		LevelMax = 4
	};
};

#endif