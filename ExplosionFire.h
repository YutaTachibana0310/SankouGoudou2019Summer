//=====================================
//
//エクスプロージョンファイアヘッダ[ExplosionFire.h]
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _EXPLOSIONFIRE_H_
#define _EXPLOSIONFIRE_H_

#include "main.h"
#include "Framework\AnimationParticle.h"
#include "Framework\BaseEmitter.h"
#include "Framework\BaseParticleController.h"

/**************************************
前方宣言
***************************************/

/**************************************
マクロ・列挙子定義
***************************************/

/**************************************
ExplosionFireクラス
***************************************/
class ExplosionFire : public AnimationParticle
{
public:
	ExplosionFire();
	void Init();
	void Update();

private:
	float speed;
	D3DXVECTOR3 moveDir;
};

/**************************************
ExplosionFireEmitterクラス
***************************************/
class ExplosionFireEmitter : public BaseEmitter
{
public:
	void Init();
	void Update();
};

/**************************************
ExplosionFireControllerクラス
***************************************/
class ExplosionFireController : public BaseParticleController
{
public:
	void Init();
	void Emit();
};

#endif