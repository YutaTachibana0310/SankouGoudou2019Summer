//=====================================
//
//�G�l�~�[�K�C�h�A���[�R���g���[������[EnemyGuideArrowController.cpp]
//Author:GP12A332 21 ���ԗY��
//
//=====================================
#include "EnemyGuideArrowController.h"
#include "EnemyGuideArrow.h"

#include "LineTrailModel.h"
#include <algorithm>

using namespace std;

/**************************************
�}�N����`
***************************************/
#define ENEMYGUIDEARROW_SIZE		(&D3DXVECTOR2(20.0f, 10.0f))
#define ENEMYGUIDEARROW_TEX_DIV		(&D3DXVECTOR2(0.5f, 1.0f))
#define ENEMYGUIDEARROW_TEX_NAME	"data/TEXTURE/Effect/GuideArrow.png"

#define ENEMYGUIDEARROW_INTERVAL	(3)

#define ENEMYGUIDEARROW_NUM_MAX		(256)
#define ENEMYGUIDEARROW_EMITTER_MAX	(16)

#define ENEMYGUIDEARROW_EMIT_NUM	(1)

typedef BaseParticleController Base;
/**************************************
����������
***************************************/
void EnemyGuideArrowController::Init()
{
	//�P�ʒ��_�o�b�t�@�쐬�A�e�N�X�`���ǂݍ���
	Base::MakeUnitBuffer(ENEMYGUIDEARROW_SIZE, ENEMYGUIDEARROW_TEX_DIV);
	Base::LoadTexture(ENEMYGUIDEARROW_TEX_NAME);

	//�p�[�e�B�N���R���e�i�쐬
	particleContainer.resize(ENEMYGUIDEARROW_NUM_MAX);
	for (auto& particle : particleContainer)
	{
		particle = new EnemyGuideArrow();
	}

	//�G�~�b�^�[�R���e�i�쐬
	emitterContainer.resize(ENEMYGUIDEARROW_EMITTER_MAX);
	for (auto& emitter : emitterContainer)
	{
		emitter = new EnemyGuideArrowEmitter();
	}

}

/**************************************
���o����
***************************************/
void EnemyGuideArrowController::Emit()
{
	Base::ForEachEmitter(ENEMYGUIDEARROW_EMIT_NUM, [](BaseEmitter* emitter, BaseParticle* particle)
	{
		if (emitter->cntFrame % ENEMYGUIDEARROW_INTERVAL != 0)
			return;

		particle->transform = emitter->transform;
		particle->Init();
	});
}

/**************************************
�G�~�b�^�[�Z�b�g����
***************************************/
void EnemyGuideArrowController::SetEmitter(LineTrailModel *model)
{
	auto itr = find_if(emitterContainer.begin(), emitterContainer.end(), [](BaseEmitter* emitter)
	{
		return !emitter->active;
	});

	if (itr == emitterContainer.end())
		return;

	EnemyGuideArrowEmitter *emitter = static_cast<EnemyGuideArrowEmitter*>(*itr);
	
	model->GetEdgePos(&emitter->start, &emitter->end);
	emitter->Init();
}