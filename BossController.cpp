//=====================================
//
//ボスコントローラ処理[BossController.cpp]
//Author:GP12A332 21 立花雄太
//
//=====================================
#include "BossController.h"

/**************************************
マクロ定義
***************************************/

/**************************************
コンストラクタ
***************************************/
BossController::BossController(const Transform& player)
{
	bossModel = new BossEnemyModel(player);
	active = false;
}

/**************************************
デストラクタ
***************************************/
BossController::~BossController()
{
	SAFE_DELETE(bossModel);
}

/**************************************
更新処理
***************************************/
void BossController::Update()
{
	if (!active)
		return;

	bossModel->Update();

	if (bossModel->IsDesteoyed())
		SetActive(false);
}

/**************************************
描画処理
***************************************/
void BossController::Draw()
{
	if (!active)
		return;

	bossModel->Draw();
}

/**************************************
アクティブセット処理
***************************************/
void BossController::SetActive(bool state)
{
	active = state;
}

bool BossController::IsActive()
{
	return active;
}
