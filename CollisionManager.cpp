//=====================================
//
//コリジョンマネージャ処理[CollisionManager.cpp]
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "CollisionManager.h"

#include "PlayerController.h"
#include "PlayerBullet.h"

#include <vector>
#include "debugWindow.h"

using namespace std;

/**************************************
マクロ定義
***************************************/

/**************************************
構造体定義
***************************************/

/**************************************
グローバル変数
***************************************/

/**************************************
プロトタイプ宣言
***************************************/
void CheckCollisionPlayerBullet();

/**************************************
更新処理
***************************************/
void UpdateCollisionManager(void)
{
	CheckCollisionPlayerBullet();
}

/**************************************
プレイヤーバレットの衝突判定
***************************************/
void CheckCollisionPlayerBullet()
{
#if 0
	vector<PlayerBullet*>* bulletContainer = GetPlayerBulletContainer();

	//エネミーとバレットの総当たり
	for (auto itrBullet = bulletContainer->begin(); itrBullet != bulletContainer->end(); itrBullet++)
	{

	}

//#ifdef _DEBUG
	//テスト用
	static TrailCollider testCollider;
	static int start, end;
	static float posZ = 500.0f;
	BeginDebugWindow("Collider");

	DebugInputInt("Start", &start);
	DebugInputInt("End", &end);
	DebugSliderFloat("Z", &posZ, 0.0f, 1000.0f);
	
	testCollider.SetAddressZ(&posZ);
	testCollider.SetTrailIndex((TrailIndex)start, (TrailIndex)end);

	for (auto itr = bulletContainer->begin(); itr != bulletContainer->end(); itr++)
	{
		if (!(*itr)->IsActive())
			continue;

		if ((*itr)->GetCollider().CheckCollision(&testCollider))
		{
			DebugText("hit!");
		}
	}

	EndDebugWindow("Begin");
#endif
}