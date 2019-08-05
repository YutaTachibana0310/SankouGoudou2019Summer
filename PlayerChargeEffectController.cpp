//=====================================
//
//�v���C���[�`���[�W�G�t�F�N�g�R���g���[������[PlayerChargeEffectController.cpp]
//Author:GP12A332 21 ���ԗY��
//
//=====================================
#include "PlayerChargeEffectController.h"
#include "PlayerChargeEffect.h"
#include "Framework\Easing.h"

/**************************************
�}�N����`
***************************************/
#define PLAYERCHARGEEFFECT_SIZE			(&D3DXVECTOR2(10.0f, 10.0f))

#define PLAYERCHARGEEFFECT_TEX_NAME		"data/TEXTURE/Effect/PlayerCharge.png"
#define PLAYERCHARGEFEFECT_TEX_DIV		(&D3DXVECTOR2(8.0f, 8.0f))

#define PLAYERCHARGEEFFECT_NUM_MAX		(512)
#define PLAYERCHARGEEFFECT_EMITTER_MAX	(4)
#define PLAYERCHARGEEFFECT_EMIT_NUM		(5)

/**************************************
����������
***************************************/
void PlayerChargeEffectController::Init()
{
	//�P�ʒ��_�o�b�t�@�쐬�A�e�N�X�`���ǂݍ���
	LoadTexture(PLAYERCHARGEEFFECT_TEX_NAME);
	MakeUnitBuffer(PLAYERCHARGEEFFECT_SIZE, PLAYERCHARGEFEFECT_TEX_DIV);

	//�p�[�e�B�N���R���e�i�쐬
	particleContainer.resize(PLAYERCHARGEEFFECT_NUM_MAX);
	for (auto& particle : particleContainer)
	{
		particle = new PlayerChargeEffect();
		static_cast<PlayerChargeEffect*>(particle)->SetAnimParameter(PLAYERCHARGEFEFECT_TEX_DIV);
	}

	//�G�~�b�^�[�R���e�i�쐬
	emitterContainer.resize(PLAYERCHARGEEFFECT_EMITTER_MAX);
	for (auto& emitter : emitterContainer)
	{
		emitter = new PlayerChargeEffectEmitter();
	}
}

/**************************************
���o����
***************************************/
void PlayerChargeEffectController::Emit()
{
	ForEachEmitter(PLAYERCHARGEEFFECT_EMIT_NUM, [](BaseEmitter* emitter, BaseParticle *particle)
	{
		particle->transform.pos = emitter->transform.pos;
		particle->Init();
	});
}
