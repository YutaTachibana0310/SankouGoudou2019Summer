//=====================================
//
//GameFailed.h
//機能:ゲームオーバーステート
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _GAMEFAILED_H_
#define _GAMEFAILED_H_

#include "main.h"
#include "IStateMachine.h"
#include "GameScene.h"

/**************************************
前方宣言
***************************************/

/**************************************
クラス定義
***************************************/
class GameScene::GameFailed : public IStateMachine<GameScene>
{
public:
	void OnStart(GameScene* entity);
	int OnUpdate(GameScene* entity);

private:
	int cntFrame;

	const int MonotoneDuration = 120;
};

#endif