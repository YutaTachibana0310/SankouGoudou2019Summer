//=====================================
//
//�G�l�~�[�o���b�g�G�t�F�N�g�R���g���[������[EnemyBulletEffectController.cpp]
//Author:GP12A332 21 ���ԗY��
//
//=====================================
#include "EnemyBulletEffectController.h"
#include "EnemyBulletEffect.h"
#include "Framework\Easing.h"

#include <algorithm>

using namespace std;
/**************************************
�}�N����`
***************************************/
#define ENEMYBULLETEFFECT_SIZE		(&D3DXVECTOR2(5.0f, 5.0f))
#define ENEMYBULLETEFFECT_TEX_DIV	(&D3DXVECTOR2(8.0f, 8.0f))
#define ENEMYBULLETEFFECT_TEX_NAME	"data/TEXTURE/Effect/EnemyBulletEffect.png"
#define ENEMYBULLETEFFECT_NUM_MAX	(1024)

#define ENEMYBULLETEFFECT_EMITTER_MAX	(32)
#define ENEMYBULLETEFFECT_EMIT_NUM		(10)

#define ENEMYBULLETEFFECT_SHRINK_LENGTH	(10.0f)

typedef BaseParticleController Base;
/**************************************
����������
***************************************/
void EnemyBulletEffectController::Init()
{
	//�P�ʒ��_�쐬�A�e�N�X�`���ǂݍ���
	Base::MakeUnitBuffer(ENEMYBULLETEFFECT_SIZE, ENEMYBULLETEFFECT_TEX_DIV);
	Base::LoadTexture(ENEMYBULLETEFFECT_TEX_NAME);

	//�p�[�e�B�N���R���e�i�쐬
	particleContainer.resize(ENEMYBULLETEFFECT_NUM_MAX);
	for (auto& particle : particleContainer)
	{
		particle = new EnemyBulletEffect();
		static_cast<EnemyBulletEffect*>(particle)->SetAnimParameter(ENEMYBULLETEFFECT_TEX_DIV);
	}

	//�G�~�b�^�[�R���e�i�쐬
	emitterContainer.resize(ENEMYBULLETEFFECT_EMITTER_MAX);
	for (auto& emitter : emitterContainer)
	{
		emitter = new EnemyBulletEffectEmitter();
	}
}

/**************************************
���o����
***************************************/
void EnemyBulletEffectController::Emit()
{
	Base::ForEachEmitter(ENEMYBULLETEFFECT_EMIT_NUM, [](BaseEmitter* emitter, BaseParticle *particle)
	{
		EnemyBulletEffectEmitter *entity = static_cast<EnemyBulletEffectEmitter*>(emitter);
		
		
		float t = RandomRangef(0.0f, 1.0f);
		particle->transform.pos = Easing::EaseValue(t, entity->edgeL, entity->edgeR, EaseType::Linear);

		particle->Init();
		
	});
}

/**************************************
�G�~�b�^�[�Z�b�g����
***************************************/
void EnemyBulletEffectController::SetEmitter(LineTrailModel model)
{
	auto itr = find_if(emitterContainer.begin(), emitterContainer.end(), [](BaseEmitter* emitter)
	{
		return !emitter->active;
	});

	if (itr == emitterContainer.end())
		return;

	EnemyBulletEffectEmitter *entity = static_cast<EnemyBulletEffectEmitter*>(*itr);

	D3DXVECTOR3 edgeR, edgeL;
	model.GetEdgePos(&edgeR, &edgeL);

	D3DXVECTOR3 diff = edgeR - edgeL;
	D3DXVec3Normalize(&diff, &diff);
	entity->edgeL = edgeL + diff * ENEMYBULLETEFFECT_SHRINK_LENGTH;
	entity->edgeR = edgeR - diff * ENEMYBULLETEFFECT_SHRINK_LENGTH;

	entity->Init();
}
