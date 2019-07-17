//=====================================
//
//ゲームバトル処理[GameBattle.cpp]
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "GameBattle.h"
#include "TrailCollider.h"
#include "EnemyController.h"
#include "InputController.h"
#include "PlayerObserver.h"

/**************************************
マクロ定義
***************************************/
#define GAMEBATTLE_DURATION		(60*10)	//とりあえずバトルを1分間だけ行う（α版用）

/**************************************
入場処理
***************************************/
void GameBattle::OnStart(GameScene *entity)
{
	entity->cntFrame = 0;
}

/**************************************
更新処理
***************************************/
int GameBattle::OnUpdate(GameScene *entity)
{
	entity->cntFrame++;

	//入力確認
	entity->playerObserver->CheckInput();

	//エネミー生成処理
	entity->enemyController->SetEnemy();

	//衝突判定
	TrailCollider::UpdateCollision();

	if (entity->cntFrame == GAMEBATTLE_DURATION) 
		return STATE_FINISHED;
	else 
		return STATE_CONTINUOUS;
	
}
