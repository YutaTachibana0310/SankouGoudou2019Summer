//=====================================
//
//�G�l�~�[�G�N�X�v���[�W��������[EnemyExplosionParticle.cpp]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "EnemyExplosionParticle.h"
#include "Framework\Easing.h"

/**************************************
�}�N����`
***************************************/
#define ENEMYEXPLOSION_SPEED_MAX	(3.0f)
#define ENEMYEXPLOSION_SPEED_MIN	(0.5f)

#define ENEMYEXPLOSION_MOVEDIR_END	(D3DXVECTOR3(0.0f, -1.0f, 0.0f))

#define ENEMYEXPLOSION_LIFE_MAX		(60)
#define ENEMYEXPLOSION_LIFE_MIN		(20)

/**************************************
EnemyExplosionParticle����������
***************************************/
void EnemyExplosionParticle::Init()
{
	cntFrame = 0;
	active = true;

	//�ړ�����������
	initMoveDir.x = RandomRangef(-1.0f, 1.0f);
	initMoveDir.y = RandomRangef(-1.0f, 1.0f);
	initMoveDir.z = RandomRangef(-1.0f, 1.0f);
	D3DXVec3Normalize(&initMoveDir, &initMoveDir);

	//�X�s�[�h����
	speed = RandomRangef(ENEMYEXPLOSION_SPEED_MIN, ENEMYEXPLOSION_SPEED_MAX);

	//��������
	lifeFrame = RandomRange(ENEMYEXPLOSION_LIFE_MIN, ENEMYEXPLOSION_SPEED_MAX);
}

/**************************************
EnemyExplosionParticle�I������
***************************************/
void EnemyExplosionParticle::Uninit()
{
	active = false;
}

/**************************************
EnemyExplosionParticle�X�V����
***************************************/
void EnemyExplosionParticle::Update()
{
	cntFrame++;

	//�A�j���[�V����
	float t = (float)cntFrame / (float)lifeFrame;
	Animation(t);

	//�ړ������ɏd�͂��ۂ��͂������Ĉړ�
	D3DXVECTOR3 moveDir = Easing<D3DXVECTOR3>::GetEasingValue(t, &initMoveDir, &ENEMYEXPLOSION_MOVEDIR_END, EasingType::InCubic);
	transform.pos += moveDir * speed;

	//��������
	if (cntFrame == lifeFrame)
	{
		active = false;
	}

}

/**************************************
EnemyExplosionEmitter����������
***************************************/
void EnemyExplosionEmitter::Init()
{
	active = true;
	cntFrame = 0;
	duration = 5;
}

/**************************************
EnemyExplosionEmitter�I������
***************************************/
void EnemyExplosionEmitter::Uninit()
{
	active = false;
}

/**************************************
EnemyExplosionPEmitter�X�V����
***************************************/
void EnemyExplosionEmitter::Update()
{
	cntFrame++;

	if (cntFrame == duration)
	{
		active = false;
	}
}