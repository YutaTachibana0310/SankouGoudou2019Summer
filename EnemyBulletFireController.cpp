//=====================================
//
//�G�l�~�[�o���b�g�t�@�C�A�R���g���[������[EnemyBulletFireController.cpp]
//Author:GP12A332 21 ���ԗY��
//
//=====================================
#include "EnemyBulletFireController.h"
#include "EnemyBulletFire.h"

/**************************************
�}�N����`
***************************************/
#define ENEMYBULLETFIRE_TEX_NAME		"data/TEXTURE/Effect/EnemyBulletFire.png"
#define ENEMYBULLETFIRE_SIZE			(&D3DXVECTOR2(3.0f, 3.0f))
#define ENEMYBULLETFIRE_TEX_DIV			(&D3DXVECTOR2(1.0f, 1.0f))

#define ENEMYBULLETFIRE_NUM_MAX			(1024)
#define ENEMYBULLETFIRE_EMITTER_MAX		(64)
#define ENEMYBULLERFIRE_EMIT_NUM		(10)

typedef BaseParticleController Base;
/**************************************
����������
***************************************/
void EnemyBulletFireController::Init()
{
	//�P�ʒ��_�o�b�t�@�쐬�A�e�N�X�`���ǂݍ���
	Base::MakeUnitBuffer(ENEMYBULLETFIRE_SIZE, ENEMYBULLETFIRE_TEX_DIV);
	Base::LoadTexture(ENEMYBULLETFIRE_TEX_NAME);

	//�p�[�e�B�N���R���e�i�쐬
	particleContainer.resize(ENEMYBULLETFIRE_NUM_MAX);
	for (auto& particle : particleContainer)
	{
		particle = new EnemyBulletFire();
	}

	//�G�~�b�^�[�R���e�i�쐬
	emitterContainer.resize(ENEMYBULLETFIRE_EMITTER_MAX);
	for (auto& emitter : emitterContainer)
	{
		emitter = new EnemyBulletFireEmitter();
	}

}

/**************************************
���o����
***************************************/
void EnemyBulletFireController::Emit()
{
	Base::ForEachEmitter(ENEMYBULLERFIRE_EMIT_NUM, [](BaseEmitter* emitter, BaseParticle* particle)
	{
		particle->transform.pos = emitter->transform.pos;
		particle->Init();
	});
}
