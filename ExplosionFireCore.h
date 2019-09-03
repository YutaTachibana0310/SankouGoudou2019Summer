//=====================================
//
//エクスプロージョンファイアコアヘッダ[ExplosionFireCore.h]
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _EXPLOSIONFIRECORE_H_
#define _EXPLOSIONFIRECORE_H_

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
ExplosionFireCoreクラス
***************************************/
class ExplosionFireCore : public BaseParticle
{
public:
	void Init();
	void Update();

	Transform *parent;
};

/**************************************
ExplosionFireCoreEmitterクラス
***************************************/
class ExplosionFireCoreEmitter : public BaseEmitter
{
public:
	void Init();
	void Update();
};

/**************************************
ExplosionFireCoreControllerクラス
***************************************/
class ExplosionFireCoreController : public BaseParticleController
{
public:
	void Init();
	void Emit();
	bool Draw();
};
#endif