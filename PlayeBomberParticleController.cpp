//=====================================
//
//プレイヤーボンバーパーティクルコントローラ処理[PlayerBomberParticleController.cpp]
//Author:GP12B332 12 権頭
//
//=====================================
#include "PlayerBomberParticleController.h"
#include "PlayerBomberParticle.h"
#include "Framework/Easing.h"

#include <algorithm>

/***************************************
マクロ定義
***************************************/
#define PLAYERBOMBERPARTICLE_TEXTURE_NAME "data/TEXTURE/Effect/PlayerBomberParticle.png"
#define PLAYERBOMBERPARTICLE_NUM_MAX		(1024)
#define PLAYERBOMBERPARTICLE_EMITTER_MAX	(24)

#define PLAYERBOMBERPARTICLE_SIZE			(&D3DXVECTOR2(6.0f,6.0f))
#define PLAYERBOMBERPARTICLE_TEX_DIV		(&D3DXVECTOR2(1.0f,1.0f))

#define PLAYERBOMBERPARTICLE_LIFEFRAME		(50)
#define PLAYERBOMBERPARTICLE_LIFE_RANGE		(3)

/************************************************
構造体定義
*************************************************/
typedef BaseParticleController Base;
/************************************************
グローバル変数
*************************************************/

/************************************************
初期化処理
*************************************************/
void PlayerBomberParticleController::Init()
{
	//単位頂点バッファ作成、テクスチャ読み込み
	Base::MakeUnitBuffer(PLAYERBOMBERPARTICLE_SIZE, PLAYERBOMBERPARTICLE_TEX_DIV);
	Base::LoadTexture(PLAYERBOMBERPARTICLE_TEXTURE_NAME);

	//パーティクルコンテナを準備
	particleContainer.resize(PLAYERBOMBERPARTICLE_NUM_MAX);
	for (UINT i = 0; i < particleContainer.size(); i++)
	{
		particleContainer[i] = new PlayerBomberParticle();
	}
	//エミッタコンテナを準備
	emitterContainer.resize(PLAYERBOMBERPARTICLE_EMITTER_MAX);
	for (UINT i = 0; i < emitterContainer.size(); i++)
	{
		emitterContainer[i] = new PlayerBomberParticleEmitter();

	}
}
/************************************************
放出処理
*************************************************/
void PlayerBomberParticleController::Emit()
{
	for (BaseEmitter* emitter : emitterContainer)
	{
		if (!emitter->active)
			continue;

		const int EmitNum = 4;		//１フレームの放出するパーティクル数
		const float InitSpeed = 0.5f;

		int emitCount = 0;
		for (BaseParticle *p : particleContainer)
		{
			if (p->active)
				continue;

			PlayerBomberParticleEmitter *entity = static_cast<PlayerBomberParticleEmitter*>(emitter);
			PlayerBomberParticle *particle = static_cast<PlayerBomberParticle*>(p);

			//移動方向設定
			particle->moveDir.x = RandomRangef(-1.0f, 1.0f);
			particle->moveDir.y = RandomRangef(-1.0f, 1.0f);
			particle->moveDir.z = -2.0f;
			D3DXVec3Normalize(&particle->moveDir, &particle->moveDir);

			//寿命、スピード設定
			particle->lifeFrame = PLAYERBOMBERPARTICLE_LIFEFRAME + RandomRange(-PLAYERBOMBERPARTICLE_LIFE_RANGE, PLAYERBOMBERPARTICLE_LIFE_RANGE);
			particle->speed = InitSpeed;

			//座標設定
			float t = RandomRangef(0.0f, 1.0f);
			particle->transform.pos = entity->transform.pos;

			//スケール設定
			particle->transform.scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

			//初期化してカウント
			particle->Init();
			emitCount++;

			//決まった数だけ放出していればbreak
			if (emitCount == EmitNum)
				break;

		}

		//決まった数だけ放出していればbreak
		if (emitCount < EmitNum)
			return;
	}
}
/********************************************d****
エミッタセット処理
*************************************************/
void PlayerBomberParticleController::SetEmitter(D3DXVECTOR3 *pPos, bool *pActive)
{
	//非アクティブのエミッタを検索
	auto itr = find_if(emitterContainer.begin(), emitterContainer.end(),
		[](BaseEmitter* p)
	{
		return !p->active;
	});

	//無かったのでリターン
	if (itr == emitterContainer.end())
		return;

	//初期化
	PlayerBomberParticleEmitter *emitter = static_cast<PlayerBomberParticleEmitter*>(*itr);
	emitter->parentActive = pActive;
	emitter->parentPos = pPos;
	emitter->Init();
}
