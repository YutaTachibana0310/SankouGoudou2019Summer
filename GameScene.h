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
#include "Framework\Polygon2D.h"

#include  <map>
/**************************************
前方宣言
***************************************/
class EnemyController;
class GameParticleManager;
class PlayerObserver;
class BackGroundController;
class BossController;
class BossUImanager;

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

	void UpdateWhole();
	void DrawWhole();

	void OnAddCombo(int n);
	void OnClearCombo();

	bool ShouldFireBomber();
	bool ShouldFireBomberOnBossBattle();

	GameScene() {};
	~GameScene() {};

	enum State
	{
		Start,
		Battle,
		End,
		BombSequence,
		BossBattle,
		BossStart,
		BossBombSequence,
		StateMax,
	};

private:
	std::map<State, IStateMachine<GameScene>*> fsm;
	IStateMachine<GameScene> *state;
	State currentState, prevState;
	Polygon2D* darkMask;

	int cntFrame;
	EnemyController *enemyController;
	GameParticleManager* particleManager;
	PlayerObserver* playerObserver;
	BackGroundController *bgController;
	BossController* bossController;
	BossUImanager* bossUI;

	bool useDarkMask;

	void ChangeState(int resultUpdate);

	int currentCombo;

	//各ステートクラス
	class GameBattle;
	class GameBomberSequence;
	class GameBossBattle;
	class GameEnd;
	class GameStart;
	class GameBossStart;
	class GameBossBombSequence;
};

#endif