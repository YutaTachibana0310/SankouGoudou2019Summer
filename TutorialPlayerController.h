//=====================================
//
//TutorialPlayerController.h
//機能:
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _TUTORIALPLAYERCONTROLLER_H_
#define _TUTORIALPLAYERCONTROLLER_H_

#include "main.h"

/**************************************
前方宣言
***************************************/
class Player;

/**************************************
クラス定義
***************************************/
class TutorialPlayerController
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

private:
	Player * player;
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