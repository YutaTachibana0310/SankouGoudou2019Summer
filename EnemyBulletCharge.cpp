//=====================================
//
//�G�l�~�[�o���b�g�`���[�W����[EnemyBulletCharge.cpp]
//Author:GP12A332 21 ���ԗY��
//
//=====================================
#include "EnemyBulletCharge.h"

/**************************************
�}�N����`
***************************************/
#define ENEMYBULLETCHARGE_POS_RANGE			(4.0f)
#define ENEMYBULLETCHARGE_EMIT_DURATION		(120)
#define ENEMYBULLETCHARGE_LIFE				(30)

/**************************************
EnemyBulletCharge����������
***************************************/
void EnemyBulletCharge::Init()
{
	cntFrame = 0;
	active = true;

	transform.Rotate(0.0f, 0.0f, RandomRangef(0.0f, 360.0f));
	transform.pos.x += RandomRangef(-ENEMYBULLETCHARGE_POS_RANGE, ENEMYBULLETCHARGE_POS_RANGE);
	transform.pos.y += RandomRangef(-ENEMYBULLETCHARGE_POS_RANGE, ENEMYBULLETCHARGE_POS_RANGE);

	lifeFrame = ENEMYBULLETCHARGE_LIFE;
}

/**************************************
EnemyBulletCharge�X�V����
***************************************/
void EnemyBulletCharge::Update()
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
EnemyBulletChargeEmitter����������
***************************************/
void EnemyBulletChargeEmitter::Init()
{
	cntFrame = 0;
	active = true;
	transform.scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	duration = ENEMYBULLETCHARGE_EMIT_DURATION;
}

/**************************************
EnemyBulletChargeEmitter�X�V����
***************************************/
void EnemyBulletChargeEmitter::Update()
{
	cntFrame++;
	
	transform.scale += D3DXVECTOR3(0.05f, 0.05f, 0.05f);
	if (cntFrame == duration)
	{
		active = false;
	}
}