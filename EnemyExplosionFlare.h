//=====================================
//
//エネミーエクスプロージョンフレアヘッダ[EnemyExplosionFlare.h]
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _ENEMYEXPLOSIONFLARE_H_
#define _ENEMYEXPLOSIONFLARE_H_

#include "main.h"
#include "Framework\BaseParticle.h"
#include "Framework\BaseEmitter.h"

/**************************************
マクロ定義
***************************************/

/**************************************
EnemyExplosionFlareクラス
***************************************/
class EnemyExplosionFlare : public BaseParticle
{
public:
	void Init();
	void Update();

private:
	D3DXVECTOR3 initMoveDir;
	D3DXVECTOR3 initScale;
	float speed;
};

/**************************************
EnemyExplosionFlareクラス
***************************************/
class EnemyExplosionFlareEmitter : public BaseEmitter
{
public:
	void Init();
	void Update();
};

#endif