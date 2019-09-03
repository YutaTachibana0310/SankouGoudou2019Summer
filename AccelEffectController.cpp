//=====================================
//
//�A�N�Z���G�t�F�N�g�R���g���[������[AccelEffectController.cpp]
//Author:GP12A332 21 ���ԗY��
//
//=====================================
#include "AccelEffectController.h"
#include "AccelEffectParticle.h"

/**************************************
�}�N����`
***************************************/
#define ACCELEEFFECT_TEX_NAME		"data/TEXTURE/Effect/AccelEffect.png"
#define ACCELEEFFECT_TEX_DIV		(&D3DXVECTOR2(1.0f, 1.0f))
#define ACCELEFFECT_SIZE			(&D3DXVECTOR2(3.0f, 25.0f))
#define ACCELEFFECT_NUM_MAX			(512)
#define ACCELEFFECT_EMITTER_MAX		(4)
#define ACCELEFFEFCT_EMIT_NUM		(50)

/**************************************
����������
***************************************/
void AccelEffectController::Init()
{
	//�P�ʒ��_�o�b�t�@�쐬�A�e�N�X�`���ǂݍ���
	MakeUnitBuffer(ACCELEFFECT_SIZE, ACCELEEFFECT_TEX_DIV);
	LoadTexture(ACCELEEFFECT_TEX_NAME);

	//�p�[�e�B�N���R���e�i�쐬
	particleContainer.resize(ACCELEFFECT_NUM_MAX);
	for (auto& particle : particleContainer)
	{
		particle = new AccelEffectParticle();
	}

	//�G�~�b�^�R���e�i�쐬
	emitterContainer.resize(ACCELEFFECT_EMITTER_MAX);
	for (auto& emitter : emitterContainer)
	{
		emitter = new AccelEffectParticleEmitter();
	}
}

/**************************************
���o����
***************************************/
void AccelEffectController::Emit()
{
	ForEachEmitter(ACCELEFFEFCT_EMIT_NUM, [](BaseEmitter *emitter, BaseParticle* particle)
	{
		particle->transform = emitter->transform;
		particle->Init();
	});
}
