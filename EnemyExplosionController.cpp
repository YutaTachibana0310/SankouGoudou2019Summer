//=====================================
//
//エネミーエクスプロージョンコントローラ処理[EnemyExplosionController.cpp]
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "EnemyExplosionController.h"
#include "EnemyExplosionParticle.h"

#include <algorithm>

/**************************************
マクロ定義
***************************************/
#define ENEMYEXPLOSION_TEXTURE_NAME		"data/TEXTURE/Effect/EnemyExplosion.png"
#define ENEMYEXPLOSION_NUM_MAX			(256)
#define ENEMYEXPLOSION_EMITTER_MAX		(64)

#define ENEMYEXPLOSION_SIZE				(&D3DXVECTOR2(15.0f, 15.0f))
#define ENEMYEXPLOSION_TEX_DIV			(&D3DXVECTOR2(8.0f, 8.0f))

#define ENEMYEXPLOSION_EMIT_NUM			(3)

typedef BaseParticleController Base;

/**************************************
初期化処理
***************************************/
void EnemyExplosionController::Init()
{
	//単位頂点バッファ作成、テクスチャ読み込み
	Base::MakeUnitBuffer(ENEMYEXPLOSION_SIZE, ENEMYEXPLOSION_TEX_DIV);
	Base::LoadTexture(ENEMYEXPLOSION_TEXTURE_NAME);

	//パーティクルコンテナを準備
	particleContainer.resize(ENEMYEXPLOSION_NUM_MAX);
	for (auto& particle : particleContainer)
	{
		particle = new EnemyExplosionParticle();
		static_cast<EnemyExplosionParticle*>(particle)->SetAnimParameter(ENEMYEXPLOSION_TEX_DIV);
	}

	//エミッタコンテナを準備
	emitterContainer.resize(ENEMYEXPLOSION_EMITTER_MAX);
	for (auto& emitter : emitterContainer)
	{
		emitter = new EnemyExplosionEmitter();
	}
}

/**************************************
放出処理
***************************************/
void EnemyExplosionController::Emit()
{

	Base::ForEachEmitter(ENEMYEXPLOSION_EMIT_NUM, 
		[](BaseEmitter *emitter, BaseParticle *particle)
	{
		//座標設定
		particle->transform.pos = emitter->transform.pos;

		//初期化してカウント
		particle->Init();
	});

}
