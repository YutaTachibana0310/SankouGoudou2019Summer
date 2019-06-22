//=====================================
//
//プレイヤーバレットパーティクルコントローラ処理[PlayerBulletParticleController.cpp]
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "PlayerBulletParticleController.h"
#include "PlayerBulletParticle.h"
#include "Framework\Easing.h"

#include <algorithm>

/**************************************
マクロ定義
***************************************/
#define PLAYERBULLETPARTICLE_TEXTURE_NAME	"data/TEXTURE/Effect/PlayerBulletParticle.png"
#define PLAYERBULLETPARTCILE_NUM_MAX		(4096)
#define PLAYERBULLETPARTICLE_EMITTER_MAX	(8)

#define PLAYERBULLETPARTICLE_SIZE			(&D3DXVECTOR2(2.0f, 2.0f))
#define PLAYERBULLETPARTICLE_TEX_DIV		(&D3DXVECTOR2(1.0f, 1.0f))

#define PLAYERBULLETPARTICLE_LIFEFRAME		(10)
#define PLAYERBULLETPARTTCLE_LIFE_RANGE		(3)

/**************************************
構造体定義
***************************************/
typedef BaseParticleController Base;

/**************************************
グローバル変数
***************************************/

/**************************************
初期化処理
***************************************/
void PlayerBulletParticleController::Init()
{
	Base::MakeUnitBuffer(PLAYERBULLETPARTICLE_SIZE, PLAYERBULLETPARTICLE_TEX_DIV);
	Base::LoadTexture(PLAYERBULLETPARTICLE_TEXTURE_NAME);

	particleContainer.resize(PLAYERBULLETPARTCILE_NUM_MAX);
	for (int i = 0; i < particleContainer.size(); i++)
	{
		particleContainer[i] = new PlayerBulletParticle();
	}

	emitterContainer.resize(PLAYERBULLETPARTICLE_EMITTER_MAX);
	for (int i = 0; i < emitterContainer.size(); i++)
	{
		emitterContainer[i] = new PlayerBulletParticleEmitter();
	}
}

/**************************************
放出処理
***************************************/
void PlayerBulletParticleController::Emit()
{
	for (BaseEmitter* emitter : emitterContainer)
	{
		if (!emitter->active)
			continue;

		const int EmitNum = 50;
		const float InitSpeed = 2.0f;

		int emitCount = 0;
		for (BaseParticle *p : particleContainer)
		{
			if (p->active)
				continue;

			PlayerBulletParticleEmitter *entity = static_cast<PlayerBulletParticleEmitter*>(emitter);
			PlayerBulletParticle *particle = static_cast<PlayerBulletParticle*>(p);

			particle->moveDir.x = RandomRangef(-1.0f, 1.0f);
			particle->moveDir.y = RandomRangef(-1.0f, 1.0f);
			particle->moveDir.z = -2.0f;
			D3DXVec3Normalize(&particle->moveDir, &particle->moveDir);

			particle->lifeFrame = PLAYERBULLETPARTICLE_LIFEFRAME + RandomRange(-PLAYERBULLETPARTTCLE_LIFE_RANGE, PLAYERBULLETPARTTCLE_LIFE_RANGE);
			particle->speed = InitSpeed;

			float t = RandomRangef(0.0f, 1.0f);
			particle->transform.pos = Easing<D3DXVECTOR3>::GetEasingValue(t, &entity->edgeLeft, &entity->edgeRight, EasingType::Linear);
			particle->transform.pos.z = entity->transform.pos.z;

			particle->transform.scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
			particle->transform.scale.x += fabsf(particle->moveDir.x) * 10.0f;
			particle->transform.scale.y += fabsf(particle->moveDir.y) * 10.0f;

			particle->Init();
			emitCount++;

			if (emitCount == EmitNum)
				break;
		}

		if (emitCount < EmitNum)
			return;

	}
}

/**************************************
エミッタセット処理
***************************************/
void PlayerBulletParticleController::SetEmitter(D3DXVECTOR3 *pPos, bool *pActive, D3DXVECTOR3 *edgeRight, D3DXVECTOR3 *edgeLeft)
{
	auto itr = find_if(emitterContainer.begin(), emitterContainer.end(),
		[](BaseEmitter* p)
	{
		return !p->active;
	});

	if (itr == emitterContainer.end())
		return;

	PlayerBulletParticleEmitter *emitter = static_cast<PlayerBulletParticleEmitter*>(*itr);
	emitter->parentActive = pActive;
	emitter->parentPos = pPos;
	emitter->edgeLeft = *edgeLeft;
	emitter->edgeRight = *edgeRight;
	emitter->Init();
}