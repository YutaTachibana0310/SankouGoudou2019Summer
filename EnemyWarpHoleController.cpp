//=====================================
//
//�G�l�~�[���[�v�z�[���R���g���[������[EnemyWarpHoleController.cpp]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "EnemyWarpHoleController.h"
#include "EnemyWarpHole.h"

/**************************************
�}�N����`
***************************************/
#define ENEMYWARPHOLE_TEXTURE_NAME		"data/TEXTURE/Effect/EnemyWarpHole.png"
#define ENEMYWARPHOLE_NUM_MAX			(512)
#define ENEMYWARPHOLE_EMITTER_MAX		(64)

#define ENEMYWARPHOLE_SIZE				(&D3DXVECTOR2(30.0f, 30.0f))
#define ENEMYWARPHOLE_TEXDIV			(&D3DXVECTOR2(8.0f, 8.0f))

#define ENEMYWARPHOLE_EMIT_NUM			(5)

typedef BaseParticleController Base;

/**************************************
����������
***************************************/
void EnemyWarpHoleController::Init()
{
	Base::MakeUnitBuffer(ENEMYWARPHOLE_SIZE, ENEMYWARPHOLE_TEXDIV);
	Base::LoadTexture(ENEMYWARPHOLE_TEXTURE_NAME);

	particleContainer.resize(ENEMYWARPHOLE_NUM_MAX);
	for (auto& particle : particleContainer)
	{
		particle = new EnemyWarpHole();
		static_cast<EnemyWarpHole*>(particle)->SetAnimParameter(ENEMYWARPHOLE_TEXDIV);
	}

	emitterContainer.resize(ENEMYWARPHOLE_EMITTER_MAX);
	for (auto& emitter : emitterContainer)
	{
		emitter = new EnemyWarpHoleEmitter();
	}
}

/**************************************
���o����
***************************************/
void EnemyWarpHoleController::Emit()
{
	ForEachEmitter(ENEMYWARPHOLE_EMIT_NUM, [](BaseEmitter *emitter, BaseParticle *particle)
	{
		particle->transform.pos = emitter->transform.pos;

		particle->Init();
	});
}