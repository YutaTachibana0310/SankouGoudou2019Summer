//=====================================
//
//ボスヒットパーティクルヘッダ[BossHitParticle.h]
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _BOSSHITPARTICLE_H_
#define _BOSSHITPARTICLE_H_

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
BossHitParticleクラス
***************************************/
class BossHitParticle : public BaseParticle
{
public:
	BossHitParticle();

	void Init();
	void Update();

private:
	float speed;
	D3DXVECTOR3 moveDir;
};

/**************************************
BossHitParticleEmitterクラス
***************************************/
class BossHitParticleEmitter : public BaseEmitter
{
	void Init();
	void Update();
};

/**************************************
BossHitParticleControllerクラス
***************************************/
class BossHitParticleController : public BaseParticleController
{
	void Init();
	void Emit();
};

#endif