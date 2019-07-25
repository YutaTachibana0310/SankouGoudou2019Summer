//=====================================
//
//�G�l�~�[�o���b�g�G�t�F�N�g����[EnemyBulletEffect.cpp]
//Author:GP12A332 21 ���ԗY��
//
//=====================================
#include "EnemyBulletEffect.h"

/**************************************
�}�N����`
***************************************/
#define ENEMYBULLETEFFECT_LIFE_MIN	(10)
#define ENEMYBULLETEFFECT_LIFE_MAX	(40)

#define ENEMYBULLETEFFECT_DURATION	(120)

#define ENEMYBULLETEFECT_POS_RANGE	(2.0f)

/**************************************
EnemyBulletEffect����������
***************************************/
void EnemyBulletEffect::Init()
{
	cntFrame = 0;
	lifeFrame = RandomRange(ENEMYBULLETEFFECT_LIFE_MIN, ENEMYBULLETEFFECT_LIFE_MAX);

	transform.Rotate(0.0f, 0.0f, RandomRangef(0.0f, 360.0f));
	transform.scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	transform.scale *= RandomRangef(0.8f, 1.5f);
	transform.pos.x += RandomRangef(-ENEMYBULLETEFECT_POS_RANGE, ENEMYBULLETEFECT_POS_RANGE);
	transform.pos.y += RandomRangef(-ENEMYBULLETEFECT_POS_RANGE, ENEMYBULLETEFECT_POS_RANGE);
	active = true;
}

/**************************************
EnemyBulletEffect�X�V����
***************************************/
void EnemyBulletEffect::Update()
{
	cntFrame++;

	float t = (float)cntFrame / (float)lifeFrame;
	Animation(t);

	if (cntFrame == lifeFrame)
		active = false;
}

/**************************************
EnemyBulletEffectEmitter����������
***************************************/
void EnemyBulletEffectEmitter::Init()
{
	cntFrame = 0;
	duration = ENEMYBULLETEFFECT_DURATION;
	active = true;
}

/**************************************
EnemyBulletEffectEmitter�X�V����
***************************************/
void EnemyBulletEffectEmitter::Update()
{
	cntFrame++;

	if (cntFrame == duration)
		active = false;
}