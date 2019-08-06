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
#include "Framework\Polygon2D.h"

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
	void DrawWhole();

	void OnAddCombo(int n);
	void OnClearCombo();

	GameScene() {};
	~GameScene() {};

	int cntFrame;
	EnemyController *enemyController;
	GameParticleManager* particleManager;
	PlayerObserver* playerObserver;
	BackGroundController *bgController;

	bool useDarkMask;

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
	Polygon2D* darkMask;

	void ChangeState(int resultUpdate);


	int currentCombo;
};

#endif