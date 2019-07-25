//=====================================
//
//�G�l�~�[�o���b�g�g���C������[EnemyBulletTrail.cpp]
//Author:GP12A332 21 ���ԗY��
//
//=====================================
#include "EnemyBulletTrail.h"

/**************************************
�}�N����`
***************************************/
#define ENEMYBULLETTRAIL_SPEED_MIN	(0.5f)
#define ENEMYBULLETTRAIL_SPEED_MAX	(4.0f)
#define ENEMYBULLETTRAIL_LIFE_MIN	(5)
#define ENEMYBULLETTRAIL_LIFE_MAX	(30)

/**************************************
EnemyBulletTrail����������
***************************************/
void EnemyBulletTrail::Init()
{
	cntFrame = 0;
	active = true;
	speed = RandomRangef(ENEMYBULLETTRAIL_SPEED_MIN, ENEMYBULLETTRAIL_SPEED_MAX);
	lifeFrame = RandomRange(ENEMYBULLETTRAIL_LIFE_MAX, ENEMYBULLETTRAIL_LIFE_MAX);
}

/**************************************
EnemyBulletTrail�X�V����
***************************************/
void EnemyBulletTrail::Update()
{
	transform.pos += speed * moveDir;

	cntFrame++;

	float t = (float)cntFrame / (float)lifeFrame;
	Animation(t);

	if (cntFrame == lifeFrame)
	{
		active = false;
	}
}

/**************************************
EnemyBulletTrailEmitter����������
***************************************/
void EnemyBulletTrailEmitter::Init()
{
	prevPos = transform.pos;
	cntFrame = 0;
	active = true;
}

/**************************************
EnemyBulletTrailEmitter�X�V����
***************************************/
void EnemyBulletTrailEmitter::Update()
{
	
}