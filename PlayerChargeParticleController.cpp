//=====================================
//
//�v���C���[�`���[�W�p�[�e�B�N���R���g���[������[PlayerChargeParticleController.cpp]
//Author:GP12A332 21 ���ԗY��
//
//=====================================
#include "PlayerChargeParticleController.h"
#include "PlayerChargeParticle.h"

/**************************************
�}�N����`
***************************************/
#define PLAYERCHARGEPARTICLE_TEX_NAME		"data/TEXTURE/Effect/PlayerBulletParticle.png"

#define PLAYERCHARGEPARTICLE_SIZE			(&D3DXVECTOR2(2.0f, 2.0f))
#define PLAYERCHARGEPARTICLE_TEX_DIV		(&D3DXVECTOR2(1.0f, 1.0f))

#define PLAYERCHARGEPARTICLE_NUM_MAX		(512)
#define PLAYERCHARGEPARTICLE_EMITTER_MAX	(4)
#define PLAYERCHARGEPARTICLE_EMIT_NUM		(20)

/**************************************
����������
***************************************/
void PlayerChargeParticleController::Init()
{
	//�P�ʒ��_�o�b�t�@�쐬�A�e�N�X�`���ǂݍ���
	MakeUnitBuffer(PLAYERCHARGEPARTICLE_SIZE, PLAYERCHARGEPARTICLE_TEX_DIV);
	LoadTexture(PLAYERCHARGEPARTICLE_TEX_NAME);

	//�p�[�e�B�N���R���e�i�쐬
	particleContainer.resize(PLAYERCHARGEPARTICLE_NUM_MAX);
	for (auto& particle : particleContainer)
	{
		particle = new PlayerChargeParticle();
	}

	//�G�~�b�^�[�R���e�i�쐬
	emitterContainer.resize(PLAYERCHARGEPARTICLE_EMITTER_MAX);
	for (auto& emitter : emitterContainer)
	{
		emitter = new PlayerChargeParticleEmitter();
	}
}

/**************************************
���o����
***************************************/
void PlayerChargeParticleController::Emit()
{
	ForEachEmitter(PLAYERCHARGEPARTICLE_EMIT_NUM, [](BaseEmitter* emitter, BaseParticle* particle)
	{
		particle->transform.pos = emitter->transform.pos;
		particle->Init();
	});
}
