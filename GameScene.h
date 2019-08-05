//=====================================
//
//�Q�[���V�[���w�b�_[GameScene.h]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _GAMESCENE_H_
#define _GAMESCENE_H_

#include "main.h"
#include "IStateScene.h"
#include "IStateMachine.h"

#include  <map>
/**************************************
�O���錾
***************************************/
class EnemyController;
class GameParticleManager;
class PlayerObserver;
class BackGroundController;

/**************************************
�N���X��`
***************************************/
class GameScene : public IStateScene
{
public:
	void Init();
	void Uninit();
	void Update(HWND hWnd);
	void Draw();

	void UpdateWhole();

	GameScene() {};
	~GameScene() {};

	int cntFrame;
	EnemyController *enemyController;
	GameParticleManager* particleManager;
	PlayerObserver* playerObserver;
	BackGroundController *bgController;

	enum State
	{
		Start,
		Battle,
		End,
		BombSequence,
		StateMax,
	};

private:
	std::map<State, IStateMachine<GameScene>*> fsm;
	IStateMachine<GameScene> *state;
	State currentState;

	void ChangeState(int resultUpdate);
};

#endif