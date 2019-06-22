//=====================================
//
//スコアパーティクルコントローラ処理[ScoreParticleController.cpp]
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "ScoreParticleController.h"
#include "ScoreParticle.h"
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
	//テクスチャ読み込み、単位頂点バッファ作成
	LoadTexture(SCOREPARTICLE_TEX_NAME);
	MakeUnitBuffer(SCOREPARTICLE_SIZE, SCOREPARTICLE_TEX_DIV);

	//パーティクルコンテナを準備
	particleContainer.resize(SCOREPARTICLE_NUM_MAX);
	for (int i = 0; i < SCOREPARTICLE_NUM_MAX; i++)
	{
		particleContainer[i] = new ScoreParticle();
	}

	//エミッタコンテナ準備
	emitterContainer.resize(SCOREPARTICLE_EMITTER_MAX);
	for (int i = 0; i < SCOREPARTICLE_EMITTER_MAX; i++)
	{
		emitterContainer[i] = new ScoreParticleEmitter();
	}
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

		int emitCount = 0;
		for (BaseParticle *p : particleContainer)
		{
			if (p->active)
				continue;

			ScoreParticle* entity = static_cast<ScoreParticle*>(p);

			//移動方向設定
			entity->moveDir.x = RandomRangef(-1.0f, 1.0f);
			entity->moveDir.y = RandomRangef(-1.0f, 1.0f);
			entity->moveDir.z = RandomRangef(-1.0f, 1.0f);

			//寿命。スピード設定
			entity->lifeFrame = SCOREPARTICLE_LIFEFRAME + RandomRange(-SCOREPARTICLE_LIFE_RANGE, SCOREPARTICLE_LIFE_RANGE);
			entity->speed = SCOREPARTICLE_SPEED_INIT + RandomRangef(-SCOREPARTICLE_SPEED_RANGE, SCOREPARTICLE_SPEED_RANGE);

			//座標設定、初期化
			entity->transform.pos = emitter->transform.pos;
			entity->Init();

			emitCount++;

			//既定数放出していればbreak
			if (emitCount == SCOREPARTICLE_EMIT_NUM)
				break;
		}

		//放出できるパーティクルが無いためリターン
		if (emitCount < SCOREPARTICLE_EMIT_NUM)
			return;
	}
}