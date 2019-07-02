//=====================================
//
//�v���C���[�o���b�g�p�[�e�B�N���R���g���[������[PlayerBulletParticleController.cpp]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "PlayerBulletParticleController.h"
#include "PlayerBulletParticle.h"
#include "Framework\Easing.h"

#include <algorithm>

/**************************************
�}�N����`
***************************************/
#define PLAYERBULLETPARTICLE_TEXTURE_NAME	"data/TEXTURE/Effect/PlayerBulletParticle.png"
#define PLAYERBULLETPARTCILE_NUM_MAX		(4096)
#define PLAYERBULLETPARTICLE_EMITTER_MAX	(8)

#define PLAYERBULLETPARTICLE_SIZE			(&D3DXVECTOR2(2.0f, 2.0f))
#define PLAYERBULLETPARTICLE_TEX_DIV		(&D3DXVECTOR2(1.0f, 1.0f))

#define PLAYERBULLETPARTICLE_LIFEFRAME		(10)
#define PLAYERBULLETPARTTCLE_LIFE_RANGE		(3)

/**************************************
�\���̒�`
***************************************/
typedef BaseParticleController Base;

/**************************************
�O���[�o���ϐ�
***************************************/

/**************************************
����������
***************************************/
void PlayerBulletParticleController::Init()
{
	//�P�ʒ��_�o�b�t�@�쐬�A�e�N�X�`���ǂݍ���
	Base::MakeUnitBuffer(PLAYERBULLETPARTICLE_SIZE, PLAYERBULLETPARTICLE_TEX_DIV);
	Base::LoadTexture(PLAYERBULLETPARTICLE_TEXTURE_NAME);

	//�p�[�e�B�N���R���e�i������
	particleContainer.resize(PLAYERBULLETPARTCILE_NUM_MAX);
	for (UINT i = 0; i < particleContainer.size(); i++)
	{
		particleContainer[i] = new PlayerBulletParticle();
	}

	//�G�~�b�^�R���e�i������
	emitterContainer.resize(PLAYERBULLETPARTICLE_EMITTER_MAX);
	for (UINT i = 0; i < emitterContainer.size(); i++)
	{
		emitterContainer[i] = new PlayerBulletParticleEmitter();
	}
}

/**************************************
���o����
***************************************/
void PlayerBulletParticleController::Emit()
{
	for (BaseEmitter* emitter : emitterContainer)
	{
		if (!emitter->active)
			continue;

		const int EmitNum = 10;			//1�t���[���̕��o����p�[�e�B�N����
		const float InitSpeed = 2.0f;	//�p�[�e�B�N���̏����X�s�[�h

		int emitCount = 0;
		for (BaseParticle *p : particleContainer)
		{
			if (p->active)
				continue;

			PlayerBulletParticleEmitter *entity = static_cast<PlayerBulletParticleEmitter*>(emitter);
			PlayerBulletParticle *particle = static_cast<PlayerBulletParticle*>(p);

			//�ړ������ݒ�
			particle->moveDir.x = RandomRangef(-1.0f, 1.0f);
			particle->moveDir.y = RandomRangef(-1.0f, 1.0f);
			particle->moveDir.z = -2.0f;
			D3DXVec3Normalize(&particle->moveDir, &particle->moveDir);

			//�����A�X�s�[�h�ݒ�
			particle->lifeFrame = PLAYERBULLETPARTICLE_LIFEFRAME + RandomRange(-PLAYERBULLETPARTTCLE_LIFE_RANGE, PLAYERBULLETPARTTCLE_LIFE_RANGE);
			particle->speed = InitSpeed;

			//���W�ݒ�
			float t = RandomRangef(0.0f, 1.0f);
			particle->transform.pos = Easing<D3DXVECTOR3>::GetEasingValue(t, &entity->edgeLeft, &entity->edgeRight, EasingType::Linear);
			particle->transform.pos.z = entity->transform.pos.z;

			//�X�P�[���ݒ�
			particle->transform.scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
			particle->transform.scale.x += fabsf(particle->moveDir.x) * 10.0f;
			particle->transform.scale.y += fabsf(particle->moveDir.y) * 10.0f;

			//���������ăJ�E���g
			particle->Init();
			emitCount++;

			//���܂������������o���Ă����break
			if (emitCount == EmitNum)
				break;
		}

		//���o�ł���p�[�e�B�N���������̂Ń��^�[��
		if (emitCount < EmitNum)
			return;

	}
}

/**************************************
�G�~�b�^�Z�b�g����
***************************************/
void PlayerBulletParticleController::SetEmitter(D3DXVECTOR3 *pPos, bool *pActive, D3DXVECTOR3 *edgeRight, D3DXVECTOR3 *edgeLeft)
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
	PlayerBulletParticleEmitter *emitter = static_cast<PlayerBulletParticleEmitter*>(*itr);
	emitter->parentActive = pActive;
	emitter->parentPos = pPos;
	emitter->edgeLeft = *edgeLeft;
	emitter->edgeRight = *edgeRight;
	emitter->Init();
}