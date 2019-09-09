//=====================================
//
//プレイヤーオブザーバーヘッダ[PlayerObserver.h]
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _PLAYEROBSERVER_H_
#define _PLAYEROBSERVER_H_

#include "main.h"

#include "IStateMachine.h"
#include "Player.h"
#include "PlayerBomberController.h"
#include "PlayerBulletController.h"
#include "PlayerModel.h"
#include "PlayerTrail.h"

#include <map>
#include <functional>
#include <vector>
#include <memory>

/**************************************
プロトタイプ宣言
***************************************/
class Enemy;

/**************************************
PlayerState列挙子
***************************************/
enum class PlayerState
{
	Move,
	Wait,
	Idle,
	Return,
	Falldown,
	Max
};

/**************************************
クラス定義
***************************************/
class PlayerObserver
{
public:
	PlayerObserver();
	~PlayerObserver();

	void Init();
	void Uninit();
	void Update();
	void Draw();
	void OnStartBomberSequence();
	void OnFinishBomberSequence();

	void CheckInput();
	void PushInput(int num);

	bool ShouldFireBomber();
	void FirePlayerBomber(std::list<std::shared_ptr<Enemy>>& targetList);
	void FirePlayerBomber(std::shared_ptr<BossEnemyModel>& targetList);
	void FirePlayerBomber(std::list<std::shared_ptr<RebarObstacle>>& targetList);

	void OnStartAccel();

	const Transform& GetPlayerTransform() const;

	PlayerModel *model;
	bool enableUpdateLogic;
	float GetHpPercent();
	bool IsAlive();

	int GetBomberStockNum();

	void OnGameOver();

private:
	Player *player;
	PlayerBomberController *bomberController;
	PlayerBulletController *bulletController;
	PlayerTrail *trailEffect;

	PlayerState current, prevState;
	std::map<PlayerState, IStateMachine<Player>*> fsm;

	int moveTarget;
	std::vector<D3DXVECTOR3> targetPos;

	void ChangeStatePlayer(PlayerState next);
	
	void TryStockBomber();

	void OnFinishPlayerMove();
	void OnFinishPlayerWait();
	void OnFinishPlayerReturn();
	void OnPlayerStateFinish();
};


#endif