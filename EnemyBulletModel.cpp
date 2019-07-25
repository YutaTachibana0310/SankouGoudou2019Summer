//=====================================
//
//エネミーバレットモデル処理[EnemyBulletModel.cpp]
//Author:GP12A332 21 立花雄太
//
//=====================================
#include "EnemyBulletModel.h"
#include "EnemyBullet.h"

/**************************************
マクロ定義
***************************************/
#define ENEMYBULLET_REACH_DEFAULT		(90)

/**************************************
コンストラクタ
***************************************/
EnemyBulletModel::EnemyBulletModel()
{
	active = false;
	posZ = 0.0f;

	collider = new TrailCollider(TrailColliderTag::EnemyBullet);
	collider->SetAddressZ(&posZ);
	collider->active = false;
}

/**************************************
デストラクタ
***************************************/
EnemyBulletModel::~EnemyBulletModel()
{
	for (auto& bullet : bullets)
	{
		SAFE_DELETE(bullet);
	}
	bullets.clear();

	SAFE_DELETE(collider);
}

/**************************************
初期化処理
***************************************/
void EnemyBulletModel::Init(std::vector<D3DXVECTOR3> emitters, LineTrailModel target)
{
	cntFrame = 0;

	collider->SetTrailIndex(target);

	bullets.reserve(emitters.size());

	D3DXVECTOR3 edgeR, edgeL;
	target.GetEdgePos(&edgeR, &edgeL);
	D3DXVECTOR3 diff = edgeL - edgeR;
	diff /= emitters.size() - 1;

	D3DXVECTOR3 targetPos = edgeR;
	for (UINT cnt = 0; cnt < emitters.size(); cnt++)
	{
		bullets.push_back(new EnemyBullet());
		bullets[cnt]->Init(emitters[cnt], targetPos, ENEMYBULLET_REACH_DEFAULT);
		targetPos += diff;
	}

}

/**************************************
終了処理
***************************************/
void EnemyBulletModel::Uninit()
{
	collider->active = false;

	for (auto& bullet : bullets)
	{
		SAFE_DELETE(bullet);
	}
	bullets.clear();
}

/**************************************
更新処理
***************************************/
void EnemyBulletModel::Update()
{
	for (auto& bullet : bullets)
	{
		bullet->Update();
	}

	cntFrame++;
}

/**************************************
描画処理
***************************************/
void EnemyBulletModel::Draw()
{
	for (auto& bullet : bullets)
	{
		bullet->Draw();
	}
}


