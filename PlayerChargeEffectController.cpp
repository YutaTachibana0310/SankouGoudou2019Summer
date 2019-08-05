//=====================================
//
//プレイヤーチャージエフェクトコントローラ処理[PlayerChargeEffectController.cpp]
//Author:GP12A332 21 立花雄太
//
//=====================================
#include "PlayerChargeEffectController.h"
#include "PlayerChargeEffect.h"
#include "Framework\Easing.h"

/**************************************
マクロ定義
***************************************/
#define PLAYERCHARGEEFFECT_SIZE			(&D3DXVECTOR2(10.0f, 10.0f))

#define PLAYERCHARGEEFFECT_TEX_NAME		"data/TEXTURE/Effect/PlayerCharge.png"
#define PLAYERCHARGEFEFECT_TEX_DIV		(&D3DXVECTOR2(8.0f, 8.0f))

#define PLAYERCHARGEEFFECT_NUM_MAX		(512)
#define PLAYERCHARGEEFFECT_EMITTER_MAX	(4)
#define PLAYERCHARGEEFFECT_EMIT_NUM		(5)

/**************************************
初期化処理
***************************************/
void PlayerChargeEffectController::Init()
{
	//単位頂点バッファ作成、テクスチャ読み込み
	LoadTexture(PLAYERCHARGEEFFECT_TEX_NAME);
	MakeUnitBuffer(PLAYERCHARGEEFFECT_SIZE, PLAYERCHARGEFEFECT_TEX_DIV);

	//パーティクルコンテナ作成
	particleContainer.resize(PLAYERCHARGEEFFECT_NUM_MAX);
	for (auto& particle : particleContainer)
	{
		particle = new PlayerChargeEffect();
		static_cast<PlayerChargeEffect*>(particle)->SetAnimParameter(PLAYERCHARGEFEFECT_TEX_DIV);
	}

	//エミッターコンテナ作成
	emitterContainer.resize(PLAYERCHARGEEFFECT_EMITTER_MAX);
	for (auto& emitter : emitterContainer)
	{
		emitter = new PlayerChargeEffectEmitter();
	}
}

/**************************************
放出処理
***************************************/
void PlayerChargeEffectController::Emit()
{
	ForEachEmitter(PLAYERCHARGEEFFECT_EMIT_NUM, [](BaseEmitter* emitter, BaseParticle *particle)
	{
		particle->transform.pos = emitter->transform.pos;
		particle->Init();
	});
}
