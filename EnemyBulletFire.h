//=====================================
//
//エネミーバレットファイアヘッダ[EnemyBulletFire.h]
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _ENEMYBULLETFIRE_H_
#define _ENEMYBULLETFIRE_H_

#include "main.h"
#include "Framework\BaseParticle.h"
#include "Framework\BaseEmitter.h"

/**************************************
マクロ定義
***************************************/

/**************************************
EnemyBulletFireクラス
***************************************/
class EnemyBulletFire : public BaseParticle
{
public:
	void Init();
	void Update();

private:
	D3DXVECTOR3 moveDir;
	float speed;
};

/**************************************
EnemyBulletエミッタクラス
***************************************/
class EnemyBulletFireEmitter : public BaseEmitter
{
public:
	void Init();
	void Update();
};

#endif