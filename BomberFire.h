//=====================================
//
//ボンバーファイアヘッダ[BomberFire.h]
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _BOBMERFIRE_H_
#define _BOBMERFIRE_H_

#include "main.h"
#include "Framework\AnimationParticle.h"
#include "Framework\BaseEmitter.h"

/**************************************
マクロ定義
***************************************/

/**************************************
BomberFireクラス
***************************************/
class BomberFire : public AnimationParticle
{
public:
	BomberFire();

	void Init();
	void Update();

private:
	D3DXVECTOR3 moveDir;
	float speed;
};

/**************************************
BomberFireEmitterクラス
***************************************/
class BomberFireEmitter : public BaseEmitter
{
public:
	void Init();
	void Update();
};

#endif