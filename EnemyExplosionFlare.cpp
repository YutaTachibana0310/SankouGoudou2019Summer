//=====================================
//
//�G�l�~�[�G�N�X�v���[�W�����t���A����[EnemyExplosionFlare.cpp]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "EnemyExplosionFlare.h"
#include "Framework\Easing.h"

/**************************************
�}�N����`
***************************************/
#define ENEMYEXPLOSIONFLARE_INIT_OFFSET		(15.0f)
#define ENEMYEXPLOSIONFLARE_LIFE_MIN		(10)
#define ENEMYEXPLOSIONFLARE_LIFE_MAX		(30)

#define ENEMYEXPLOSIONFLARE_MOVEDIR_END		(D3DXVECTOR3(0.0f, -1.0f, 0.0f))

#define ENEMYEXPLOSIONFLARE_SPEED_MIN		(2.8f)
#define ENEMYEXPLOSIONFLARE_SPEED_MAX		(3.5f)

#define ENEMYEXPLOSIONFLARE_EMIT_DURATION	(10)

/**************************************
EnemyExplosionFlare����������
***************************************/
void EnemyExplosionFlare::Init()
{
	//�ړ�����������
	initMoveDir.x = RandomRangef(-1.0f, 1.0f);
	initMoveDir.y = RandomRangef(-1.0f, 1.0f);
	initMoveDir.z = RandomRangef(-1.0f, 1.0f);
	D3DXVec3Normalize(&initMoveDir, &initMoveDir);

	//�ړ������֏������W���ړ�������
	transform.pos += initMoveDir * ENEMYEXPLOSIONFLARE_INIT_OFFSET;

	//�����ݒ�A�J�E���^������
	cntFrame = 0;
	lifeFrame = RandomRange(ENEMYEXPLOSIONFLARE_LIFE_MIN, ENEMYEXPLOSIONFLARE_LIFE_MAX);

	//�X�s�[�h�ݒ�
	speed = RandomRangef(ENEMYEXPLOSIONFLARE_SPEED_MIN, ENEMYEXPLOSIONFLARE_SPEED_MAX);

	//�����X�P�[���ۑ�
	initScale = transform.scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	active = true;
}

/**************************************
EnemyExplosionFlare�X�V����
***************************************/
void EnemyExplosionFlare::Update()
{
	cntFrame++;

	//�ړ������ɏd�͂��������Ă���ۂ�����
	float t = (float)cntFrame / (float)lifeFrame;
	D3DXVECTOR3 moveDir = Easing::EaseValue(t, initMoveDir, ENEMYEXPLOSIONFLARE_MOVEDIR_END, EaseType::InCubic);

	//�ړ�����
	transform.pos += moveDir * speed;

	//�X�P�[������
	transform.scale = Easing::EaseValue(t, initScale, D3DXVECTOR3(0.0f, 0.0f, 0.0f), EaseType::InExpo);

	//��������
	if (cntFrame == lifeFrame)
	{
		active = false;
	}
}

/**************************************
EnemyExplosionFlareEmitter����������
***************************************/
void EnemyExplosionFlareEmitter::Init()
{
	cntFrame = 0;
	duration = ENEMYEXPLOSIONFLARE_EMIT_DURATION;
	active = true;
}

/**************************************
EnemyExplosionFlareEmitter�X�V����
***************************************/
void EnemyExplosionFlareEmitter::Update()
{
	cntFrame++;

	//��������
	if (cntFrame == duration)
	{
		active = false;
	}
}