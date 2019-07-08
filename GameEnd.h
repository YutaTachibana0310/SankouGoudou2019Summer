//=====================================
//
//ゲームエンドヘッダ[GameEnd.h]
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _GAMEEND_H_
#define _GAMEEND_H_

#include "main.h"
#include "IStateMachine.h"
#include "GameScene.h"

/**************************************
マクロ定義
***************************************/

/**************************************
クラス定義
***************************************/
class GameEnd : public IStateMachine<GameScene>
{
public:
	void OnStart(GameScene *entity);
	int OnUpdate(GameScene *entity);
};

#endif