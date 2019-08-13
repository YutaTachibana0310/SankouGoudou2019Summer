//=====================================
//
//�v���C���[�{���o�[�p�[�e�B�N���R���g���[������[PlayerBomberParticleController.cpp]
//Author:GP12B332 12 ����
//
//=====================================
#include "PlayerBomberParticleController.h"
#include "PlayerBomberParticle.h"
#include "Framework/Easing.h"

#include <algorithm>

/***************************************
�}�N����`
***************************************/
#define PLAYERBOMBERPARTICLE_TEXTURE_NAME "data/TEXTURE/Effect/PlayerBomberParticle.png"
#define PLAYERBOMBERPARTICLE_NUM_MAX		(1024)
#define PLAYERBOMBERPARTICLE_EMITTER_MAX	(24)

#define PLAYERBOMBERPARTICLE_SIZE			(&D3DXVECTOR2(6.0f,6.0f))
#define PLAYERBOMBERPARTICLE_TEX_DIV		(&D3DXVECTOR2(1.0f,1.0f))

/************************************************
�\���̒�`
*************************************************/
typedef BaseParticleController Base;
/************************************************
�O���[�o���ϐ�
*************************************************/

/************************************************
����������
*************************************************/
void PlayerBomberParticleController::Init()
{
	//�P�ʒ��_�o�b�t�@�쐬�A�e�N�X�`���ǂݍ���
	Base::MakeUnitBuffer(PLAYERBOMBERPARTICLE_SIZE, PLAYERBOMBERPARTICLE_TEX_DIV);
	Base::LoadTexture(PLAYERBOMBERPARTICLE_TEXTURE_NAME);

	//�p�[�e�B�N���R���e�i������
	particleContainer.resize(PLAYERBOMBERPARTICLE_NUM_MAX);
	for (UINT i = 0; i < particleContainer.size(); i++)
	{
		particleContainer[i] = new PlayerBomberParticle();
	}
	//�G�~�b�^�R���e�i������
	emitterContainer.resize(PLAYERBOMBERPARTICLE_EMITTER_MAX);
	for (UINT i = 0; i < emitterContainer.size(); i++)
	{
		emitterContainer[i] = new PlayerBomberParticleEmitter();

	}
}
/************************************************
���o����
*************************************************/
void PlayerBomberParticleController::Emit()
{
	for (BaseEmitter* emitter : emitterContainer)
	{
		if (!emitter->active)
			continue;

		const int EmitNum = 8;		//�P�t���[���̕��o����p�[�e�B�N����
		const float InitSpeed = 0.5f;

		int emitCount = 0;
		for (BaseParticle *p : particleContainer)
		{
			if (p->active)
				continue;

			PlayerBomberParticleEmitter *entity = static_cast<PlayerBomberParticleEmitter*>(emitter);
			PlayerBomberParticle *particle = static_cast<PlayerBomberParticle*>(p);

			////�ړ������ݒ�
			D3DXVECTOR3 dir = entity->prevPos - entity->transform.pos;
			D3DXVec3Normalize(&dir, &dir);
			particle->SetMoveDir(dir);

			//���W�ݒ�
			particle->transform.pos = entity->transform.pos;

			//���������ăJ�E���g
			particle->Init();
			emitCount++;

			//���܂������������o���Ă����break
			if (emitCount == EmitNum)
				break;

		}

		//���܂������������o���Ă����break
		if (emitCount < EmitNum)
			return;
	}
}
/********************************************d****
�G�~�b�^�Z�b�g����
*************************************************/
void PlayerBomberParticleController::SetEmitter(D3DXVECTOR3 *pPos, bool *pActive)
{
	//��A�N�e�B�u�̃G�~�b�^������
	auto itr = find_if(emitterContainer.begin(), emitterContainer.end(),
		[](BaseEmitter* p)
	{
		return !p->active;

	});

	//���������̂Ń��^�[��
	if (itr == emitterContainer.end())
		return;

	//������
	PlayerBomberParticleEmitter *emitter = static_cast<PlayerBomberParticleEmitter*>(*itr);
	emitter->parentActive = pActive;
	emitter->parentPos = pPos;
	emitter->Init();
}
