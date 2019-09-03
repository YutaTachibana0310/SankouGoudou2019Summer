//=====================================
//
//�G�N�X�v���[�W�����t�@�C�A�R�A����[ExplosionFireCore.cpp]
//Author:GP12A332 21 ���ԗY��
//
//=====================================
#include "ExplosionFireCore.h"
#include "Framework\Easing.h"
#include "Framework\Vector3.h"

/**************************************
ExplosionFireCore����������
***************************************/
void ExplosionFireCore::Init()
{
	cntFrame = 0;
	active = true;
	lifeFrame = RandomRange(5, 10);
}

/**************************************
ExplosionFireCore�X�V����
***************************************/
void ExplosionFireCore::Update()
{
	cntFrame++;

	transform.pos = parent->pos;
	if (cntFrame == lifeFrame)
	{
		active = false;
	}
}

/**************************************
ExplosionFireCoreEmitter����������
***************************************/
void ExplosionFireCoreEmitter::Init()
{
	cntFrame = 0;
	active = true;
	duration = 240;
}

/**************************************
ExplosionFireCoreEmitter�X�V����
***************************************/
void ExplosionFireCoreEmitter::Update()
{
	cntFrame++;

	float t = 1.0f * cntFrame / duration;
	transform.scale = Vector3::One * Easing::EaseValue(t, 0.05f, 25.0f, EaseType::InExpo);
	
	if (cntFrame == duration)
	{
		active = false;
	}
}

/**************************************
ExplosionFireCoreController����������
***************************************/
void ExplosionFireCoreController::Init()
{
	MakeUnitBuffer(&D3DXVECTOR2(300.0f, 300.0f), &D3DXVECTOR2(1.0f, 1.0f));
	LoadTexture("data/TEXTURE/Effect/ExplosionFireCharge.png");

	particleContainer.resize(128);
	for (auto&& particle : particleContainer)
	{
		particle = new ExplosionFireCore();
	}

	emitterContainer.resize(1);
	for (auto&& emitter : emitterContainer)
	{
		emitter = new ExplosionFireCoreEmitter();
	}
}

/**************************************
ExplosionFireCoreController���o����
***************************************/
void ExplosionFireCoreController::Emit()
{
	ForEachEmitter(1, [](BaseEmitter* emitter, BaseParticle *particle)
	{
		particle->transform = emitter->transform;
		static_cast<ExplosionFireCore*>(particle)->parent = &emitter->transform;
		particle->Init();
	});
}

/**************************************
ExplosionFireCoreController�`�揈��
***************************************/
bool ExplosionFireCoreController::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	//pDevice->SetRenderState(D3DRS_ZENABLE, false);

	bool res = BaseParticleController::Draw();

	pDevice->SetRenderState(D3DRS_ZENABLE, true);

	return res;
}
