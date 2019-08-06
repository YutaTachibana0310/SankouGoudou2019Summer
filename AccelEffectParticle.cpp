//=====================================
//
//�A�N�Z���G�t�F�N�g�p�[�e�B�N������[AccelEffectParticle.cpp]
//Author:GP12A332 21 ���ԗY��
//
//=====================================
#include "AccelEffectParticle.h"
#include "Framework\Easing.h"

/**************************************
�}�N����`
***************************************/
#define ACCELEFFECT_LIFEFRAME		(20)
#define ACCELEFFECT_SCALE			(5.0f)
#define ACCELEFFECT_POS_OFFSET		(3.0f)
#define ACCELEFFECT_SPEED			(10.0f)

/**************************************
AccelEffectParticle����������
***************************************/
void AccelEffectParticle::Init()
{
	cntFrame = 0;
	active = true;

	//�ړ���������
	moveDir.x = RandomRangef(-1.0f, 1.0f);
	moveDir.y = RandomRangef(-1.0f, 1.0f);
	moveDir.z = -1.0f;
	D3DXVec3Normalize(&moveDir, &moveDir);

	//�X�P�[������
	baseScale = D3DXVECTOR3(fabsf(moveDir.x), fabsf(moveDir.y), 0.0f);
	D3DXVec3Normalize(&baseScale, &baseScale);
	baseScale.z = 1.0f;

	//���W�I�t�Z�b�g
	transform.pos += moveDir * ACCELEFFECT_POS_OFFSET;

	//��������
	lifeFrame = ACCELEFFECT_LIFEFRAME;
}

/**************************************
AccelEffectParticle�X�V����
***************************************/
void AccelEffectParticle::Update()
{
	cntFrame++;

	//�ړ�
	transform.pos += moveDir * ACCELEFFECT_SPEED;

	//�X�P�[���C�[�W���O
	float t = (float)cntFrame / lifeFrame;
	transform.scale = Easing::EaseValue(t, 1.0f, 0.0f, EaseType::InCubic) * baseScale;

	if (cntFrame == lifeFrame)
		active = false;

}

/**************************************
AccelEffectParticleEmitter����������
***************************************/
void AccelEffectParticleEmitter::Init()
{
	cntFrame = 0;
	duration = 5;
	active = true;
}

/**************************************
AccelEffectParticleEmitter�X�V����
**************************************/
void AccelEffectParticleEmitter::Update()
{
	cntFrame++;

	if (cntFrame == duration)
		active = false;
}