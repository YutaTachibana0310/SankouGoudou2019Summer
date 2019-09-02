//=====================================
//
//ボスバトルボンバーシーケンスヘッダ[GameBossBombSequence.h]
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _GAMEBOSSBOMBSEQUENCE_H_
#define _GAMEBOSSBOMBSEQUENCE_H_

#include "main.h"
#include "IStateMachine.h"
#include "GameScene.h"

/**************************************
前方宣言
***************************************/

/**************************************
クラス定義
***************************************/
class GameScene::GameBossBombSequence : public IStateMachine<GameScene>
{
public:
	void OnStart(GameScene* entity);
	int OnUpdate(GameScene* entity);

private:
	int cntFrame;
};
#endif