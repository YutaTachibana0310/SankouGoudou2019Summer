//=====================================
//
//�G�l�~�[�G�N�X�v���[�W�����t���A�R���g���[������[EnemyExplosionFlareController.cpp]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "EnemyExplosionFlareController.h"
#include "EnemyExplosionFlare.h"

#include <algorithm>

/**************************************
�}�N����`
***************************************/
#define ENEMYEXPLOSIONFLARE_MAX			(1024)
#define ENEMYEXPLOSIONFLARE_EMIT_MAX	(64)

#define ENEMYEXPLOSIONFLARE_SIZE		(&D3DXVECTOR2(4.0f, 4.0f))
#define ENEMYEXPLOSIONFLARE_TEX_DIV		(&D3DXVECTOR2(1.0f, 1.0f))
#define ENEMYEXPLOSIONFLARE_TEX_NAME	"data/TEXTURE/Effect/EnemyExplosionFlare.png"

#define ENEMYEXPLOSIONFLARE_EMIT_NUM	(10)

typedef BaseParticleController Base;

/**************************************
����������
***************************************/
void EnemyExplosionFlareController::Init()
{
	//�P�ʒ��_�o�b�t�@�쐬�A�e�N�X�`���ǂݍ���
	Base::MakeUnitBuffer(ENEMYEXPLOSIONFLARE_SIZE, ENEMYEXPLOSIONFLARE_TEX_DIV);
	Base::LoadTexture(ENEMYEXPLOSIONFLARE_TEX_NAME);

	//�p�[�e�B�N���R���e�i����
	particleContainer.resize(ENEMYEXPLOSIONFLARE_MAX);
	for (auto& particle : particleContainer)
	{
		particle = new EnemyExplosionFlare();
	}

	//�G�~�b�^�R���e�i����
	emitterContainer.resize(ENEMYEXPLOSIONFLARE_EMIT_MAX);
	for (auto& emitter : emitterContainer)
	{
		emitter = new EnemyExplosionFlareEmitter();
	}
}

/**************************************
���o���� 
***************************************/
void EnemyExplosionFlareController::Emit()
{
	for (auto& emitter : emitterContainer)
	{
		if (!emitter->active)
			continue;

		const int EmitNum = ENEMYEXPLOSIONFLARE_EMIT_NUM;

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