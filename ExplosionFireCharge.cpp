//=====================================
//
//�e���v���[�g����[Template.cpp]
//Author:GP12A332 21 ���ԗY��
//
//=====================================
#include "ExplosionFireCharge.h"
#include "Framework\Easing.h"
#include "Framework\Vector3.h"

/**************************************
�}�N����`
***************************************/

/**************************************
ExplosionFireCharge�R���X�g���N�^
***************************************/
ExplosionFireCharge::ExplosionFireCharge()
{
	lifeFrame = RandomRange(60, 180);

	D3DXVECTOR3 moveDir;
	moveDir.x = RandomRangef(-1.0f, 1.0f);
	moveDir.y = RandomRangef(-1.0f, 1.0f);
	moveDir.z = RandomRangef(-1.0f, 1.0f);

	D3DXVec3Normalize(&moveDir, &moveDir);

	const float Speed = RandomRangef(5.0f, 10.0f);
	offset = moveDir * (float)lifeFrame * Speed;	

}

/**************************************
ExplosionFireCharge����������
***************************************/
void ExplosionFireCharge::Init()
{
	cntFrame = 0;
	active = true;
}

/**************************************
ExplosionFireCharge�X�V����
***************************************/
void ExplosionFireCharge::Update()
{
	cntFrame++;

	float t = (float)cntFrame / lifeFrame;
	transform.pos = parent->pos - Easing::EaseValue(t, offset, Vector3::Zero, EaseType::InExpo);
	
	transform.scale = Vector3::One * Easing::EaseValue(t, 0.0f, 2.0f, EaseType::InSine);

	if (cntFrame == lifeFrame)
	{
		active = false;
	}
}

/**************************************
ExplosionFireChargeEmitter����������
***************************************/
void ExplosionFireChargeEmitter::Init()
{
	duration = 120;
	cntFrame = 0;
	active = true;
}

/**************************************
ExplosionFireChargeEmitter�X�V����
***************************************/
void ExplosionFireChargeEmitter::Update()
{
	cntFrame++;
	if (cntFrame == duration)
	{
		active = false;
	}
}

/**************************************
ExplosionFireChargeController����������
***************************************/
void ExplosionFireChargeController::Init()
{
	MakeUnitBuffer(&D3DXVECTOR2(20.0f, 20.0f), &D3DXVECTOR2(1.0f, 1.0f));
	LoadTexture("data/TEXTURE/Effect/ExplosionFireCharge.png");

	particleContainer.resize(1024);
	for (auto&& particle : particleContainer)
	{
		particle = new ExplosionFireCharge();
	}

	emitterContainer.resize(2);
	for (auto&& emitter : emitterContainer)
	{
		emitter = new ExplosionFireChargeEmitter();
	}
}

/**************************************
ExplosionFireChargeController���o����
***************************************/
void ExplosionFireChargeController::Emit()
{
	ForEachEmitter(3, [](BaseEmitter* emitter, BaseParticle *particle)
	{
		particle->transform = emitter->transform;
		static_cast<ExplosionFireCharge*>(particle)->parent = &emitter->transform;
		particle->Init();
	});
}

/**************************************
ExplosionFireChargeController�`�揈��
***************************************/
bool ExplosionFireChargeController::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	//pDevice->SetRenderState(D3DRS_ZENABLE, false);

	bool res = BaseParticleController::Draw();

	pDevice->SetRenderState(D3DRS_ZENABLE, true);

	return res;
}
