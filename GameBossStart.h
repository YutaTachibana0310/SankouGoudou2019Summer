//=====================================
//
//ゲームボススタートヘッダ[GameBossStart.h]
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _GAMEBOSSSTART_H_
#define _GAMEBOSSSTART_H_

#include "main.h"
#include "IStateMachine.h"
#include "GameScene.h"

/**************************************
前方宣言
***************************************/

/**************************************
マクロ・列挙子定義
***************************************/

/**************************************
クラス定義
***************************************/
class GameScene::GameBossStart : public IStateMachine<GameScene>
{
public:
	void OnStart(GameScene* entity);
	int OnUpdate(GameScene* entity);
};

#endif