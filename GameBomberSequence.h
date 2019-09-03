//=====================================
//
//ボンバーシーケンスヘッダ[GameBomberSequence.h]
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _GAMEBOMBERSEQUENCE_H_
#define _GAMEBOMBERSEQUENCE_H_

#include "main.h"
#include "IStateMachine.h"
#include "GameScene.h"

/**************************************
マクロ定義
***************************************/

/**************************************
クラス定義
***************************************/
class GameScene::GameBomberSequence : public IStateMachine<GameScene>
{
	int OnUpdate(GameScene* entity);
	void OnStart(GameScene* entity);

private:
	int cntFrame;
};

#endif