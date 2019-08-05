//=====================================
//
//�G�l�~�[�o���b�g�g���C���R���g���[������[EnemyBulletTrailController.cpp]
//Author:GP12A332 21 ���ԗY��
//
//=====================================
#include "EnemyBulletTrailController.h"
#include "EnemyBulletTrail.h"

/**************************************
�}�N����`
***************************************/
#define ENEMYBULLETTRAIL_SIZE			(&D3DXVECTOR2(10.0f, 10.0f))
#define ENEMYBULLETTRAIL_TEX_DIV		(&D3DXVECTOR2(8.0f, 8.0f))
#define ENEMYBULLETTRAIL_TEX_NAME		"data/TEXTURE/Effect/EnemyBulletTrail.png"
#define ENEMYBULLETTRAIL_NUM_MAX		(1024)
#define ENEMYBULLETTRAIL_EMITTER_MAX	(32)
#define ENEMYBULLETTRAIL_EMIT_NUM		(5)

typedef BaseParticleController Base;
/**************************************
����������
***************************************/
void EnemyBulletTrailController::Init()
{
	//���_�o�b�t�@�ݒ�A�e�N�X�`���ǂݍ���
	Base::MakeUnitBuffer(ENEMYBULLETTRAIL_SIZE, ENEMYBULLETTRAIL_TEX_DIV);
	Base::LoadTexture(ENEMYBULLETTRAIL_TEX_NAME);

	//�p�[�e�B�N���R���e�i�쐬
	particleContainer.resize(ENEMYBULLETTRAIL_NUM_MAX);
	for (auto& particle : particleContainer)
	{
		particle = new EnemyBulletTrail();
		static_cast<AnimationParticle*>(particle)->SetAnimParameter(ENEMYBULLETTRAIL_TEX_DIV);
	}

	//�G�~�b�^�[�R���e�i�쐬
	emitterContainer.resize(ENEMYBULLETTRAIL_EMITTER_MAX);
	for(auto& emitter : emitterContainer)
	{ 
		emitter = new EnemyBulletTrailEmitter();
	}
}

/**************************************
���o����
***************************************/
void EnemyBulletTrailController::Emit()
{
	//���o
	Base::ForEachEmitter(ENEMYBULLETTRAIL_EMIT_NUM, [](BaseEmitter *emitter, BaseParticle *particle)
	{
		//���W�ݒ�
		particle->transform.pos = emitter->transform.pos;

		//�ړ������ݒ�
		EnemyBulletTrail *entityParticle = static_cast<EnemyBulletTrail*>(particle);
		EnemyBulletTrailEmitter *entityEmitter = static_cast<EnemyBulletTrailEmitter*>(emitter);
		entityParticle->moveDir = entityEmitter->prevPos - entityEmitter->transform.pos;
		D3DXVec3Normalize(&entityParticle->moveDir, &entityParticle->moveDir);

		//������
		particle->Init();
	});

	//���݈ʒu��ۑ�
	for (auto& emitter : emitterContainer)
	{
		if (!emitter->active)
			continue;

		EnemyBulletTrailEmitter *entity = static_cast<EnemyBulletTrailEmitter*>(emitter);
		entity->prevPos = entity->transform.pos;
	}
}