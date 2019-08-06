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
#define ACCELEFFECT_LIFE_MIN		(10)
#define ACCELEFFECT_LIFE_MAX		(20)
#define ACCELEFFECT_SCALE			(5.0f)
#define ACCELEFFECT_POS_OFFSET		(5.0f)
#define ACCELEFFECT_SPEED			(8.0f)
#define ACCELEFFECT_MOVE_Z			(-2.0f)

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
	moveDir.z = -0.0f;
	D3DXVec3Normalize(&moveDir, &moveDir);

	//��]
	float dir = moveDir.x > 0.0f ? 1.0f : -1.0f;
	float dot = D3DXVec3Dot(&moveDir, &D3DXVECTOR3(0.0f, 1.0f, 0.0f));
	transform.Rotate(0.0f, 0.0f, D3DXToDegree(acosf(dot)) * dir);

	//���W�I�t�Z�b�g
	transform.pos.x += moveDir.x * ACCELEFFECT_POS_OFFSET;
	transform.pos.y += moveDir.y * ACCELEFFECT_POS_OFFSET;

	//��������
	lifeFrame = RandomRange(ACCELEFFECT_LIFE_MIN, ACCELEFFECT_LIFE_MAX);
	
	moveDir.z = ACCELEFFECT_MOVE_Z;
}

/**************************************
AccelEffectParticle�X�V����
***************************************/
void AccelEffectParticle::Update()
{
	cntFrame++;
	float t = (float)cntFrame / lifeFrame;

	//�X�s�[�h�C�[�W���O
	float speed = Easing::EaseValue(t, ACCELEFFECT_SPEED, 0.3f, EaseType::OutCubic);
	transform.pos += moveDir * speed;

	//�X�P�[���C�[�W���O
	transform.scale.x = Easing::EaseValue(t, 1.0f, 0.0f, EaseType::InCubic);

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