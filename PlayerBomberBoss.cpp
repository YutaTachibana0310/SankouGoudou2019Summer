//=====================================
//
//PlayerBomberBoss.cpp
//機能:ボスを追尾するボンバー
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "PlayerBomberBoss.h"
#include "BossEnemyModel.h"
#include "Framework\CameraShakePlugin.h"

/**************************************
グローバル変数
***************************************/

/**************************************
更新処理
***************************************/
void PlayerBomberBoss::Update()
{
	if (!active)
		return;

	std::shared_ptr<BossEnemyModel> ptr = target.lock();

	//参照先が有効であればターゲット座標を更新
	if (ptr)
	{
		targetPos = ptr->GetPosition();
	}

	//追尾処理
	Homing();

	//着弾タイミングの判定
	if (cntFrame == 0)
	{
		//着弾処理
		if (ptr)
		{
			const D3DXVECTOR3 ShakeAmplitude = D3DXVECTOR3(10.0f, 10.0f, 10.0f);
			const int ShakeDuration = 60;

			//カメラを揺らす
			Camera::ShakePlugin::Instance()->Set(ShakeAmplitude, ShakeDuration);
			ptr->OnHitBomber();
		}

		Uninit();
	}

}

/**************************************
セット処理
***************************************/
void PlayerBomberBoss::Set(std::shared_ptr<BossEnemyModel>& target, D3DXVECTOR3 initPos)
{
	const int ReachFrame = 40;

	this->target = target;
	transform.pos = initPos;
	cntFrame = reachFrame = ReachFrame;
}
