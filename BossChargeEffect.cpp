//=====================================
//
//�{�X�`���[�W�p�[�e�B�N������[BossChargeParticle.cpp]
//Author:GP12A332 21 ���ԗY��
//
//=====================================
#include "BossChargeEffect.h"

/**************************************
�}�N����`
***************************************/

/**************************************
BossChargeParticle�R���X�g���N�^
***************************************/
BossChargeParticle::BossChargeParticle()
{
	SetAnimParameter(&D3DXVECTOR2(8.0f, 8.0f));
}

/**************************************
BossChargeParticle������
***************************************/
void BossChargeParticle::Init()
{
	cntFrame = 0;
	active = true;

	transform.Rotate(0.0f, 0.0f, RandomRangef(0.0f, 360.0f));

	const float PosRange = 5.0f * transform.scale.x;
	transform.pos.x += RandomRangef(-PosRange, PosRange);
	transform.pos.y += RandomRangef(-PosRange, PosRange);

	lifeFrame = 60;
}

/**************************************
BossChargeParticle�X�V����
***************************************/
void BossChargeParticle::Update()
{
	cntFrame++;

	float t = (float)cntFrame / lifeFrame;
	Animation(t);

	if (cntFrame == lifeFrame)
	{
		active = false;
	}
}

/**************************************
BossChargeEmitter������
***************************************/
void BossChargeEmitter::Init()
{
	cntFrame = 0;
	active = true;
	transform.scale = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	duration = 90;
}

/**************************************
BossChargeEmitter�X�V����
***************************************/
void BossChargeEmitter::Update()
{
	cntFrame++;

	const float DeltaScale = 0.02f;
	transform.scale += D3DXVECTOR3(1.0f, 1.0f, 1.0f) * DeltaScale;

	if (cntFrame == duration)
	{
		active = false;
	}
}

/**************************************
BossChargeParticleController������
***************************************/
void BossChargeParticleController::Init()
{
	MakeUnitBuffer(&D3DXVECTOR2(30.0f, 30.0f), &D3DXVECTOR2(8.0f, 8.0f));
	LoadTexture("data/TEXTURE/EFFECT/EnemyBulletCharge.png");

	particleContainer.resize(1023);
	for (auto&& particle : particleContainer)
	{
		particle = new BossChargeParticle();
	}

	emitterContainer.resize(4);
	for (auto&& emitter : emitterContainer)
	{
		emitter = new BossChargeEmitter();
	}
}

/**************************************
BossChargeParticlrController���o����
***************************************/
void BossChargeParticleController::Emit()
{
	ForEachEmitter(5, [](BaseEmitter* emitter, BaseParticle* particle)
	{
		particle->transform = emitter->transform;
		particle->Init();
	});
}