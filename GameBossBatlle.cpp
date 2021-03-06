//=====================================
//
//ゲームボスバトル処理[GameBossBattle.cpp]
//Author:GP12A332 21 立花雄太
//
//=====================================
#include "GameBossBattle.h"
#include "BossController.h"
#include "PlayerObserver.h"

/**************************************
マクロ定義
***************************************/

/**************************************
入場処理
***************************************/
void GameScene::GameBossBattle::OnStart(GameScene* entity)
{
	entity->bossController->SetActive(true);
}

/**************************************
更新処理
***************************************/
int GameScene::GameBossBattle::OnUpdate(GameScene* entity)
{
	int result = GameScene::State::BossBattle;

	entity->cntFrame++;

	//入力確認
	entity->playerObserver->CheckInput();

	//プレイヤーの位置情報をボスに渡す
	int playerIndex = entity->playerObserver->GetCurrentPosition();
	entity->bossController->PassPlayerPosition(playerIndex);

	//ゲーム全体を更新
	entity->UpdateWhole();

	//ボンバー発射判定
	if (entity->ShouldFireBomberOnBossBattle())
		result = GameScene::State::BossBombSequence;

	//衝突判定
	TrailCollider::UpdateCollision();
	BoxCollider3D::UpdateCollision();

	//ボスの撃破判定
	if (!entity->bossController->IsActive())
	{
		result = GameScene::State::End;
	}

	//ゲームオーバー判定
	if (!entity->playerObserver->IsAlive())
	{
		result = GameScene::State::Failed;
	}

	return result;
}
