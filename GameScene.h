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

	GameScene() {};
	~GameScene() {};

	int cntFrame;
	EnemyController *enemyController;
	GameParticleManager* particleManager;

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