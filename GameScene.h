//=====================================
//
//ゲームシーンヘッダ[GameScene.h]
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _GAMESCENE_H_
#define _GAMESCENE_H_

#include "main.h"
#include "IStateScene.h"
#include "IStateMachine.h"

#include  <map>
/**************************************
前方宣言
***************************************/
class GameSceneUI;
class EnemyController;
class GameParticleManager;
class PlayerObserver;
class BackGroundController;

/**************************************
クラス定義
***************************************/
class GameScene : public IStateScene
{
public:
	void Init();
	void Uninit();
	void Update(HWND hWnd);
	void Draw();

	GameScene() {};
	~GameScene() {};

	int cntFrame;

	GameSceneUI *gameSceneUI;
	EnemyController *enemyController;
	GameParticleManager* particleManager;
	PlayerObserver* playerObserver;
	BackGroundController *bgController;

private:
	
	enum class State
	{
		Idle,
		Start,
		Battle,
		End,
	};

	std::map<State, IStateMachine<GameScene>*> fsm;
	IStateMachine<GameScene> *state;
	State currentState;

	void ChangeState(int resultUpdate);
};

#endif