//=====================================
//
//RebarExplosion.cpp
//�@�\:�S���̔����G�t�F�N�g
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "RebarExplosion.h"

/**************************************
�O���[�o���ϐ�
***************************************/

/**************************************
RebarExplosion�R���X�g���N�^
***************************************/
RebarExplosion::RebarExplosion()
{
	SetAnimParameter(&D3DXVECTOR2(8.0f, 8.0f));
}

/**************************************
RebarExplosion����������
***************************************/
void RebarExplosion::Init()
{
	const float PosRange = 10.0f;

	transform.pos.x += RandomRangef(-PosRange, PosRange);
	transform.pos.y += RandomRangef(-PosRange, PosRange);
	transform.pos.z += RandomRangef(-PosRange, PosRange);

	transform.Rotate(0.0f, 0.0f, RandomRangef(0.0f, 360.0f));

	const int LifeMin = 60;
	const int LifeMax = 90;

	cntFrame = 0;
	lifeFrame = RandomRange(LifeMin, LifeMax);
	active = true;
}

/**************************************
RebarExplosion�X�V����
***************************************/
void RebarExplosion::Update()
{
	cntFrame++;

	float t = 1.0f * cntFrame / lifeFrame;

	Animation(t);

	if (cntFrame == lifeFrame)
	{
		active = false;
	}
}

/**************************************
RebarExplosionEmitter����������
***************************************/
void RebarExplosionEmitter::Init()
{
	cntFrame = 0;
	duration = 5;
	active = true;
}

/**************************************
RebarExplosionEmitter�X�V����
***************************************/
void RebarExplosionEmitter::Update()
{
	cntFrame++;

	if (cntFrame == duration)
	{
		active = false;
	}
}

/**************************************
RebarExplosionController����������
***************************************/
void RebarExplosionController::Init()
{
	MakeUnitBuffer(&D3DXVECTOR2(25.0f, 25.0f), &D3DXVECTOR2(8.0f, 8.0f));
	LoadTexture("data/TEXTURE/Effect/ExplosionFire.png");

	particleContainer.resize(256);
	for (auto&& particle : particleContainer)
	{
		particle = new RebarExplosion();
	}

	emitterContainer.resize(64);
	for (auto&& emitter : emitterContainer)
	{
		emitter = new RebarExplosionEmitter();
	}
}

/**************************************
RearExplosionController���o����
***************************************/
void RebarExplosionController::Emit()
{
	ForEachEmitter(3, [](BaseEmitter* emitter, BaseParticle* particle)
	{
		particle->transform = emitter->transform;
		particle->Init();
	});
}
