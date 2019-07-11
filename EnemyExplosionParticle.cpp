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
#define ENEMYEXPLOSION_MOVEDIR_END	(D3DXVECTOR3(0.0f, -1.0f, 0.0f))

#define ENEMYEXPLOSION_LIFE_MAX		(50)
#define ENEMYEXPLOSION_LIFE_MIN		(20)

#define ENEMYEXPLOSIONEMITTER_DURATION	(5)

/**************************************
EnemyExplosionParticle����������
***************************************/
void EnemyExplosionParticle::Init()
{
	cntFrame = 0;
	active = true;

	//���W�����炷
	const float PosRange = 5.0f;
	transform.pos.x += RandomRangef(-PosRange, PosRange);
	transform.pos.y += RandomRangef(-PosRange, PosRange);
	transform.pos.z += RandomRangef(-PosRange, PosRange);

	//��������
	lifeFrame = RandomRange(ENEMYEXPLOSION_LIFE_MIN, ENEMYEXPLOSION_LIFE_MAX);

	//��]
	transform.Rotate(0.0f, 0.0f, RandomRangef(0.0f, 360.0f));

	//�X�P�[��
	transform.scale.x = transform.scale.y = transform.scale.z = RandomRangef(1.0f, 1.5f);
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
	duration = ENEMYEXPLOSIONEMITTER_DURATION;
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