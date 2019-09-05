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
BossController::BossController(const Transform& player, BossUImanager& manager)
{
	bossModel = std::make_shared<BossEnemyModel>(player, manager);
	active = false;
}

/**************************************
デストラクタ
***************************************/
BossController::~BossController()
{
	bossModel.reset();
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

/**************************************
アクティブ判定
***************************************/
bool BossController::IsActive()
{
	return active;
}

/**************************************
ボスポインタ取得処理
***************************************/
std::shared_ptr<BossEnemyModel> BossController::GetBoss()
{
	return bossModel;
}

/**************************************
鉄骨リスト取得処理
***************************************/
void BossController::GetRebarList(std::list<std::shared_ptr<RebarObstacle>>& out)
{
	bossModel->GetRebarList(out);
}
