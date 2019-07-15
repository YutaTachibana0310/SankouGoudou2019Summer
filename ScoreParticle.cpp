//=====================================
//
//�X�R�A�p�[�e�B�N������[ScoreParticle.cpp]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "ScoreParticle.h"
#include "Framework\Easing.h"

#include <algorithm>

using namespace std;

/**************************************
�}�N����`
***************************************/
#define SCOREPARTICLE_SIZE			(10.0f)
#define SCOREPARTICLE_NUM_MAX		(256)

#define SCOREPARTICLE_TEX_NAME		("data/TEXTURE/Effect/ScoreParticle.png")
#define SCOREPARTICLE_TEX_DIV_X		(1)
#define SCOREPARTICLE_TEX_DIV_Y		(1)
#define SCOREPARTICLE_ANIM_TIME		(1)

#define SCOREPARTICLE_LIFEFRAME		(40)
#define SCOREPARTICLE_LIFE_RANGE	(10)
#define SCOREPARTICLE_SPEED_INIT	(2.0f)
#define SCOREPARTICLE_SPEED_RANGE	(2.0f)
#define SCOREPARTICLE_SPEED_TIME	(10.0f)

#define SCOREPARTICLE_DURATION		(5)
#define SCOREPARTICLE_EMIT_NUM		(10)

/**************************************
ScoreParticle����������
***************************************/
void ScoreParticle::Init()
{
	cntFrame = 0;
	active = true;

	//�ړ������ݒ�
	moveDir.x = RandomRangef(-1.0f, 1.0f);
	moveDir.y = RandomRangef(-1.0f, 1.0f);
	moveDir.z = RandomRangef(-1.0f, 1.0f);

	//�����B�X�s�[�h�ݒ�
	lifeFrame = SCOREPARTICLE_LIFEFRAME + RandomRange(-SCOREPARTICLE_LIFE_RANGE, SCOREPARTICLE_LIFE_RANGE);
	speed = SCOREPARTICLE_SPEED_INIT + RandomRangef(-SCOREPARTICLE_SPEED_RANGE, SCOREPARTICLE_SPEED_RANGE);
}

/**************************************
ScoreParticle�I������
***************************************/
void ScoreParticle::Uninit()
{
	active = false;
}

/**************************************
ScoreParticle�X�V��������
***************************************/
void ScoreParticle::Update()
{
	const float EndSpeed = 0.2f;
	const float InitScale = 1.0f, EndScale = 0.0f;

	if (!active)
		return;

	//�ړ�����
	float tSpeed = (float)cntFrame / (float)SCOREPARTICLE_SPEED_TIME;
	float currentSpeed = Easing<float>::GetEasingValue(tSpeed, &speed, &EndSpeed, EasingType::InExponential);
	transform.pos += moveDir * currentSpeed;

	//�X�P�[������
	float tScale = (float)cntFrame / (float)lifeFrame;
	float currentScale = Easing<float>::GetEasingValue(tScale, &InitScale, &EndScale, EasingType::OutExponential);
	transform.scale = D3DXVECTOR3(currentScale, currentScale, currentScale);

	//��������
	cntFrame++;
	if (cntFrame > lifeFrame)
	{
		active = false;
	}
}

/**************************************
ScoreParticleEmitter�R���X�g���N�^
***************************************/
ScoreParticleEmitter::ScoreParticleEmitter(D3DXVECTOR3 *pos) : BaseEmitter(pos)
{
	cntFrame = 0;
	duration = SCOREPARTICLE_DURATION;
	active = true;
}

/**************************************
ScoreParticleEmitter����������
***************************************/
void ScoreParticleEmitter::Init()
{
	cntFrame = 0;
	duration = SCOREPARTICLE_DURATION;
	active = true;
}

/**************************************
ScoreParticleEmitter�I������
***************************************/
void ScoreParticleEmitter::Uninit()
{
	active = false;
}

/**************************************
ScoreParticleEmitter�X�V����
***************************************/
void ScoreParticleEmitter::Update()
{
	if (!active)
		return;

	//��������
	cntFrame++;
	if (cntFrame > duration)
	{
		active = false;
	}
}