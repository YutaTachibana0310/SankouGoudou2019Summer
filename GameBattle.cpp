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
#include "sound.h"

/**************************************
マクロ定義
***************************************/
#define GAMEBATTLE_DURATION		(60*60)	//とりあえずバトルを1分間だけ行う（α版用）

/**************************************
入場処理
***************************************/
void GameBattle::OnStart(GameScene *entity)
{
	entity->cntFrame = 0;
	Sound::GetInstance()->playsound = true;
}

/**************************************
更新処理
***************************************/
int GameBattle::OnUpdate(GameScene *entity)
{
	int result = GameScene::State::Battle;

	entity->cntFrame++;

	//入力確認
	entity->playerObserver->CheckInput();

	//エネミー生成処理
	entity->enemyController->SetEnemy();

	//ゲーム全体を更新
	entity->UpdateWhole();

	//一筆書き判定
	if (entity->playerObserver->IsCompletedOneStroke())
		result = GameScene::State::BombSequence;

	//衝突判定
	TrailCollider::UpdateCollision();

	//終了判定
	if (entity->cntFrame == GAMEBATTLE_DURATION)
		result = GameScene::State::End;

	return result;
	
}
