//=====================================
//
//�G�l�~�[�o���b�g�`���[�W�R���g���[������[EnemyBulletChargeController.cpp]
//Author:GP12A332 21 ���ԗY��
//
//=====================================
#include "EnemyBulletChargeController.h"
#include "EnemyBulletCharge.h"

/**************************************
�}�N����`
***************************************/
#define ENEMYBULLETCHARGE_TEX_NAME		"data/TEXTURE/EFFECT/EnemyBulletCharge.png"

#define ENEMYBULLETCHARGE_NUM_MAX		(1024)
#define ENEMYBULLETCHARGE_EMITTER_MAX	(64)

#define ENEMYBULLETCHARGE_EMIT_NUM		(2)

#define ENEMYBULLETCHARGE_SIZE			(&D3DXVECTOR2(2.0f, 2.0f))
#define ENEMYBULLETCHARGE_TEX_DIV		(&D3DXVECTOR2(8.0f, 8.0f))

typedef BaseParticleController Base;
/**************************************
����������
***************************************/
void EnemyBulletChargeController::Init()
{
	//�P�ʒ��_�o�b�t�@�쐬�A�e�N�X�`���ǂݍ���
	Base::LoadTexture(ENEMYBULLETCHARGE_TEX_NAME);
	Base::MakeUnitBuffer(ENEMYBULLETCHARGE_SIZE, ENEMYBULLETCHARGE_TEX_DIV);

	//�p�[�e�B�N���R���e�i�쐬
	particleContainer.resize(ENEMYBULLETCHARGE_NUM_MAX);
	for (auto& particle : particleContainer)
	{
		particle = new EnemyBulletCharge();
		static_cast<EnemyBulletCharge*>(particle)->SetAnimParameter(ENEMYBULLETCHARGE_TEX_DIV);
	}

	//�G�~�b�^�[�R���e�i�쐬
	emitterContainer.resize(ENEMYBULLETCHARGE_EMITTER_MAX);
	for (auto& emitter : emitterContainer)
	{
		emitter = new EnemyBulletChargeEmitter();
	}
}

/**************************************
���o����
***************************************/
void EnemyBulletChargeController::Emit()
{
	ForEachEmitter(ENEMYBULLETCHARGE_EMIT_NUM, [](BaseEmitter *emitter, BaseParticle *particle)
	{
		particle->transform = emitter->transform;

		particle->Init();
	});
}
