//=====================================
//
//スコアパーティクルコントローラ処理[ScoreParticleController.cpp]
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "ScoreParticleController.h"
#include <algorithm>

using namespace std;

/**************************************
マクロ定義
***************************************/
#define SCOREPARTICLE_NUM_MAX		(256)
#define SCOREPARTICLE_EMITTER_MAX	(32)

#define SCOREPARTICLE_SIZE			(&D3DXVECTOR2(10.0f, 10.0f))

#define SCOREPARTICLE_TEX_NAME		("data/TEXTURE/Effect/ScoreParticle.png")
#define SCOREPARTICLE_TEX_DIV		(&D3DXVECTOR2(1.0f, 1.0f))

#define SCOREPARTICLE_LIFEFRAME		(40)
#define SCOREPARTICLE_LIFE_RANGE	(10)
#define SCOREPARTICLE_SPEED_INIT	(2.0f)
#define SCOREPARTICLE_SPEED_RANGE	(2.0f)
#define SCOREPARTICLE_SPEED_TIME	(10.0f)

#define SCOREPARTICLE_DURATION		(5)
#define SCOREPARTICLE_EMIT_NUM		(10)
/**************************************
構造体定義
***************************************/
typedef BaseParticleController Base;

/**************************************
グローバル変数
***************************************/

/**************************************
プロトタイプ宣言
***************************************/

/**************************************
初期化処理
***************************************/
void ScoreParticleController::Init()
{
	LoadTexture(SCOREPARTICLE_TEX_NAME);
	MakeUnitBuffer(SCOREPARTICLE_SIZE, SCOREPARTICLE_TEX_DIV);

	particleContainer.resize(SCOREPARTICLE_NUM_MAX);
	for (int i = 0; i < SCOREPARTICLE_NUM_MAX; i++)
	{
		particleContainer[i] = new ScoreParticle();
	}

	emitterContainer.resize(SCOREPARTICLE_EMITTER_MAX);
	for (int i = 0; i < SCOREPARTICLE_EMITTER_MAX; i++)
	{
		emitterContainer[i] = new ScoreParticleEmitter();
	}
}

/**************************************
発生処理
***************************************/
void ScoreParticleController::SetEmitter(D3DXVECTOR3 *pos)
{
	auto emitter = find_if(emitterContainer.begin(), emitterContainer.end(), [](BaseEmitter* emitter) { return emitter->active; });

	if (emitter == emitterContainer.end())
		return;

	(*emitter)->transform.pos = *pos;
	(*emitter)->Init();

}

/**************************************
放出処理
***************************************/
void ScoreParticleController::Emit()
{
	int emitterMax = emitterContainer.size();

	for (BaseEmitter *emitter : emitterContainer)
	{
		if (!emitter->active)
			continue;

		for (int i = 0; i < SCOREPARTICLE_EMIT_NUM; i++)
		{
			auto particle = find_if(particleContainer.begin(), particleContainer.end(), [](BaseParticle* p) {return !p->active; });

			if (particle == particleContainer.end())
				return;

			ScoreParticle* entity = static_cast<ScoreParticle*>(*particle);
			D3DXVECTOR3 moveDir;
			moveDir.x = RandomRangef(-1.0f, 1.0f);
			moveDir.y = RandomRangef(-1.0f, 1.0f);
			moveDir.z = RandomRangef(-1.0f, 1.0f);

			int lifeFrame = SCOREPARTICLE_LIFEFRAME + RandomRange(-SCOREPARTICLE_LIFE_RANGE, SCOREPARTICLE_LIFE_RANGE);
			float speed = SCOREPARTICLE_SPEED_INIT + RandomRangef(-SCOREPARTICLE_SPEED_RANGE, SCOREPARTICLE_SPEED_RANGE);

			entity->SetParameter(speed, &moveDir, lifeFrame);
			entity->transform.pos = emitter->transform.pos;
			entity->Init();
		}
	}
}