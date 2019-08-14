//=====================================
//
//�{���o�[�t�@�C�A�R���g���[������[BomberFireController.cpp]
//Author:GP12A332 21 ���ԗY��
//
//=====================================
#include "BomberFireController.h"
#include "BomberFire.h"

/**************************************
�}�N����`
***************************************/
#define BOBMERFIRE_TEXTURE_NAME		"data/TEXTURE/Effect/BomberFire.png"
#define BOMBERFIRE_TEXTURE_DIV		(&D3DXVECTOR2(8.0f, 8.0f))
#define BOMBERFIRE_SIZE				(&D3DXVECTOR2(5.0f, 5.0f))
#define BOMBERFIRE_NUM_MAX			(512)
#define BOMBERFIRE_EMITTER_NUM		(1)
#define BOMBERFIRE_EMIT_NUM			(170)

/**************************************
����������
***************************************/
void BomberFireController::Init()
{
	//�P�ʒ��_�o�b�t�@�쐬�A�e�N�X�`�����[�h
	MakeUnitBuffer(BOMBERFIRE_SIZE, BOMBERFIRE_TEXTURE_DIV);
	LoadTexture(BOBMERFIRE_TEXTURE_NAME);

	//�p�����[�^�R���e�i�쐬
	particleContainer.resize(BOMBERFIRE_NUM_MAX);
	for (auto& particle : particleContainer)
	{
		particle = new BomberFire();
	}

	//�G�~�b�^�R���e�i�쐬
	emitterContainer.resize(BOMBERFIRE_EMITTER_NUM);
	for (auto& emitter : emitterContainer)
	{
		emitter = new BomberFireEmitter();
	}
}

/**************************************
���o����
***************************************/
void BomberFireController::Emit()
{
	ForEachEmitter(BOMBERFIRE_EMIT_NUM, [](BaseEmitter* emitter, BaseParticle* particle)
	{
		particle->transform.pos = emitter->transform.pos;
		particle->Init();
	});
}

