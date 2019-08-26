//=====================================
//
//ゲームバトルヘッダ[GameBattle.h]
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _GAMEBATTLE_H_
#define _GAMEBATTLE_H_

#include "main.h"
#include "IStateMachine.h"
#include "GameScene.h"

/**************************************
マクロ定義
***************************************/

/**************************************
クラス定義
***************************************/
class GameScene::GameBattle: public IStateMachine<GameScene>
{
public:
	void OnStart(GameScene* entity);
	int OnUpdate(GameScene* entity);
};

#endif