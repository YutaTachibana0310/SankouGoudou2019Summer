//=====================================
//
//TutorialScene::TutorialIdle.cpp
//機能:
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "TutorialIdle.h"
#include "TutorialScene.h"
#include "TutorialBG.h"
#include "GameSceneUIManager.h"
#include "PlayerObserver.h"
#include "PlayerController.h"
#include "InputController.h"
#include "GameParticleManager.h"
#include "TutorialController.h"
#include "TutorialEnemyController.h"
#include "ScoreManager.h"

/**************************************
グローバル変数
***************************************/

/**************************************
入場処理
***************************************/
void TutorialScene::TutorialIdle::OnStart(TutorialScene * entity)
{
	//特にやることなし
}

/**************************************
更新処理
***************************************/
int TutorialScene::TutorialIdle::OnUpdate(TutorialScene * entity)
{
	int result = TutorialScene::State::Idle;
	//入力確認
	entity->playerObserver->CheckInput();

	//ボンバー発射確認
	if (entity->ShouldFireBomber())
	{

		result = TutorialScene::State::Bomber;
	}

	//各オブジェクト更新
	entity->bg->Update();
	entity->playerObserver->Update();
	entity->enemyController->Update();

	//チュートリアルガイド更新
	entity->controller->Update();

	//パーティクル更新
	GameParticleManager::Instance()->Update();

	//衝突判定
	TrailCollider::UpdateCollision();
	BoxCollider3D::UpdateCollision();

	return result;
}
