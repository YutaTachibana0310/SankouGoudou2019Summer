//=====================================
//
//�G�l�~�[�o���b�g�t�@�C�A����[EnemyBulletFire.cpp]
//Author:GP12A332 21 ���ԗY��
//
//=====================================
#include "EnemyBulletFire.h"
#include "Framework\Easing.h"

/**************************************
�}�N����`
***************************************/
#define ENEMYBULLETFIRE_LIFE_MIN	(10)
#define ENEMYBULLETFIRE_LIFE_MAX	(30)

#define ENEMYBULLETFIRE_SPEED_MAX	(10.0f)
#define ENEMYBULLETFIRE_SPEED_MIN	(5.0f)

/**************************************
EnemyBulletFire����������
***************************************/
void EnemyBulletFire::Init()
{
	cntFrame = 0;
	active = true;

	lifeFrame = RandomRange(ENEMYBULLETFIRE_LIFE_MIN, ENEMYBULLETFIRE_LIFE_MAX);

	moveDir.x = RandomRangef(-1.0f, 1.0f);
	moveDir.y = RandomRangef(-1.0f, 1.0f);
	moveDir.z = 1.0f;
	D3DXVec3Normalize(&moveDir, &moveDir);

	speed = RandomRangef(ENEMYBULLETFIRE_SPEED_MIN, ENEMYBULLETFIRE_SPEED_MAX);
}

/**************************************
EnemyBulletFire�X�V����
***************************************/
void EnemyBulletFire::Update()
{
	static const float EndSpeed = 0.0f;
	static const float InitScale = 1.0f;
	static const float EndScale = 0.0f;

	cntFrame++;
	float t = (float)cntFrame / lifeFrame;

	
	float currentSpeed = Easing<float>::GetEasingValue(t, &speed, &EndSpeed, EasingType::OutCubic);
	transform.pos += moveDir * currentSpeed;

	transform.scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f) * Easing<float>::GetEasingValue(t, &InitScale, &EndScale, EasingType::InExponential);

	if (cntFrame == lifeFrame)
		active = false;
}

/**************************************
EnemyBulletFireEmitter����������
***************************************/
void EnemyBulletFireEmitter::Init()
{
	cntFrame = 0;
	active = true;

	duration = 5;
}

/**************************************
EnemyBulletFireEmitter�X�V����
***************************************/
void EnemyBulletFireEmitter::Update()
{
	cntFrame++;

	if (cntFrame == duration)
		active = false;
}