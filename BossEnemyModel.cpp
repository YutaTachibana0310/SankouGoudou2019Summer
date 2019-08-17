//=====================================
//
//ボスエネミーモデル処理[BossEnemyModel.cpp]
//Author:GP12A332 21 立花雄太
//
//=====================================
#include "BossEnemyModel.h"
#include "BossEnemyActor.h"

/**************************************
マクロ定義
***************************************/

/**************************************
コンストラクタ
***************************************/
BossEnemyModel::BossEnemyModel()
{
	actor = new BossEnemyActor();

	actor->transform.pos = D3DXVECTOR3(0.0f, -200.0f, -2000.0f);
	actor->transform.Rotate(0.0f, 180.0f, 0.0f);
	actor->Move(D3DXVECTOR3(0.0f, -200.0f, 1500.0f), 300);

	actor->ChangeAnimation(BossEnemyActor::AnimID::Flying);
}

/**************************************
デストラクタ
***************************************/
BossEnemyModel::~BossEnemyModel()
{
	SAFE_DELETE(actor);
}

/**************************************
更新処理
***************************************/
int BossEnemyModel::Update()
{
	actor->Update();
	return 0;
}

/**************************************
描画処理
***************************************/
void BossEnemyModel::Draw()
{
	actor->Draw();
}