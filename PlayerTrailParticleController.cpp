//=====================================
//
//プレイヤートレイルパーティクルコントローラ処理[PlayerTrailParticleController.cpp]
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "PlayerTrailParticleController.h"
#include "PlayerTrailParticle.h"

using namespace std;

/**************************************
マクロ定義
***************************************/

/**************************************
構造体定義
***************************************/

/**************************************
グローバル変数
***************************************/

/**************************************
PlayerTrailParticleController初期化処理
***************************************/
void PlayerTrailParticleController::Init()
{
	const D3DXVECTOR2 Size = D3DXVECTOR2(2.0f, 2.0f);
	const D3DXVECTOR2 TexDiv = D3DXVECTOR2(2.0f, 2.0f);
	const char* TextureName = "data/TEXTURE/Effect/PlayerTrailParticle.png";

	MakeUnitBuffer(&Size, &TexDiv);
	LoadTexture(TextureName);

	const int ParticleMax = 256;
	const int EmitterMax = 1;

	particleContainer.resize(ParticleMax);
	for (UINT i = 0; i < ParticleMax; i++)
	{
		particleContainer[i] = new PlayerTrailParticle();
	}

	emitterContainer.resize(EmitterMax);
	emitterContainer[0] = new PlayerTrailEmitter();
}

/**************************************
PlayerTrailParticleController更新処理
***************************************/
void PlayerTrailParticleController:: Emit()
{
	PlayerTrailEmitter *emitter = static_cast<PlayerTrailEmitter*>(emitterContainer[0]);

	if (!emitter->active)
		return;

	const int EmitNum = 5;
	const float PosRangeXZ = 12.0f;
	const float PosRangeY = 2.0f;

	int emitCount = 0;
	for (BaseParticle *particle : particleContainer)
	{
		if (particle->active)
			continue;

		PlayerTrailParticle *entity = static_cast<PlayerTrailParticle*>(particle);

		//初期座標設定
		entity->transform.pos = emitter->transform.pos;
		entity->transform.pos.x += RandomRangef(-PosRangeXZ, PosRangeXZ);
		entity->transform.pos.y += RandomRangef(-PosRangeXZ, PosRangeXZ);
		entity->transform.pos.z += RandomRangef(-PosRangeXZ, PosRangeXZ);

		//初期化してカウント
		entity->Init();
		
		emitCount++;

		if (emitCount == EmitNum)
			return;
	}
}

/**************************************
PlayerTrailParticleControllerエミッタセット処理
***************************************/
void PlayerTrailParticleController::SetEmitter(D3DXVECTOR3 *pPos, bool *pActive)
{
	PlayerTrailEmitter *emitter = static_cast<PlayerTrailEmitter*>(emitterContainer[0]);
	emitter->SetParent(pPos, pActive);
	emitter->active = true;
}