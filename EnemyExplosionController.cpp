//=====================================
//
//�G�l�~�[�G�N�X�v���[�W�����R���g���[������[EnemyExplosionController.cpp]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "EnemyExplosionController.h"
#include "EnemyExplosionParticle.h"

#include <algorithm>

/**************************************
�}�N����`
***************************************/
#define ENEMYEXPLOSION_TEXTURE_NAME		"data/TEXTURE/Effect/EnemyExplosion.png"
#define ENEMYEXPLOSION_NUM_MAX			(512)
#define ENEMYEXPLOSION_EMITTER_MAX		(64)

#define ENEMYEXPLOSION_SIZE				(&D3DXVECTOR2(15.0f, 15.0f))
#define ENEMYEXPLOSION_TEX_DIV			(&D3DXVECTOR2(8.0f, 8.0f))

#define ENEMYEXPLOSION_EMIT_NUM			(3)

typedef BaseParticleController Base;

/**************************************
����������
***************************************/
void EnemyExplosionController::Init()
{
	//�P�ʒ��_�o�b�t�@�쐬�A�e�N�X�`���ǂݍ���
	Base::MakeUnitBuffer(ENEMYEXPLOSION_SIZE, ENEMYEXPLOSION_TEX_DIV);
	Base::LoadTexture(ENEMYEXPLOSION_TEXTURE_NAME);

	//�p�[�e�B�N���R���e�i������
	particleContainer.resize(ENEMYEXPLOSION_NUM_MAX);
	for (auto& particle : particleContainer)
	{
		particle = new EnemyExplosionParticle();
		static_cast<EnemyExplosionParticle*>(particle)->SetAnimParameter(ENEMYEXPLOSION_TEX_DIV);
	}

	//�G�~�b�^�R���e�i������
	emitterContainer.resize(ENEMYEXPLOSION_EMITTER_MAX);
	for (auto& emitter : emitterContainer)
	{
		emitter = new EnemyExplosionEmitter();
	}
}

/**************************************
���o����
***************************************/
void EnemyExplosionController::Emit()
{
	for (auto& emitter : emitterContainer)
	{
		if (!emitter->active)
			continue;

		const int EmitNum = ENEMYEXPLOSION_EMIT_NUM;

		int emitCount = 0;
		for (auto& particle : particleContainer)
		{
			if (particle->active)
				continue;

			//���W�ݒ�
			particle->transform.pos = emitter->transform.pos;

			//���������ăJ�E���g
			particle->Init();
			emitCount++;

			//���܂������������o���Ă�����break
			if (emitCount == EmitNum)
				break;
		}

		//���o�ł���p�[�e�B�N���������̂Ń��^�[��
		if (emitCount < EmitNum)
			return;
	}

}
