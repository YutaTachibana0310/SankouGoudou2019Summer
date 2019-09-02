//=====================================
//
//エネミーを追尾するボンバー処理[PlayerBomberEnemy.cpp]
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "PlayerBomberEnemy.h"
#include "enemy.h"
#include "Framework\CameraShakePlugin.h"

/**************************************
グローバル変数
***************************************/

/**************************************
更新処理
***************************************/
void PlayerBomberEnemy::Update()
{
	if (!active)
		return;

	std::shared_ptr<Enemy> ptr = target.lock();

	//参照先が有効であればターゲット座標を更新
	if (ptr)
	{
		targetPos = ptr->m_Pos;
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
void PlayerBomberEnemy::Set(std::shared_ptr<Enemy>& target, D3DXVECTOR3 initPos)
{
	this->target = target;
	PlayerBomber::Set(initPos);
}
