//=====================================
//
//エクスプロージョンファイアチャージヘッダ[ExplosionFireCharge.h]
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _EXPLOSIONFIRECHARGE_H_
#define _EXPLOSIONFIRECHARGE_H_

#include "main.h"
#include "Framework\BaseParticle.h"
#include "Framework\BaseEmitter.h"
#include "Framework\BaseParticleController.h"

/**************************************
前方宣言
***************************************/

/**************************************
マクロ・列挙子定義
***************************************/

/**************************************
ExplisionFireChargeクラス
***************************************/
class ExplosionFireCharge : public BaseParticle
{
public:
	ExplosionFireCharge();
	void Init();
	void Update();

	Transform *parent;

private:
	D3DXVECTOR3 offset;
};

/**************************************
ExplisionFireChageEmitterクラス
***************************************/
class ExplosionFireChargeEmitter : public BaseEmitter
{
public:
	void Init();
	void Update();
};

/**************************************
ExplisionFireChargeControllerクラス
***************************************/
class ExplosionFireChargeController : public BaseParticleController
{
public:
	void Init();
	void Emit();
	bool Draw();
};

#endif