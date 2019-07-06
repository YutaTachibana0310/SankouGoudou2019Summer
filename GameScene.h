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

/**************************************
前方宣言
***************************************/
class EnemyController;
class GameParticleManager;

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

private:
	EnemyController *enemyController;
	GameParticleManager* particleManager;
};

#endif