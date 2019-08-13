//=====================================
//
//�v���C���[�{���o�[�p�[�e�B�N������[PlayerBomberParticle.cpp]
//Author:GP12B332 12 ����
//
//=====================================
#include "PlayerBomberParticle.h"

/**************************************
�}�N����`
***************************************/
#define BOMBER_PARTICLE_ROT			(2.0f)
#define BOMBERTRAIL_LIFE_MIN		(15)
#define BOMBERTRAIL_LIFE_MAX		(25)
#define BOMBERTRAIL_SPEED_MAX		(2.0f)
#define BOMBERTRAIL_SPEED_MIN		(0.5f)

/**************************************
PlayerBomberParticle����������
***************************************/
void PlayerBomberParticle::Init()
{
	active = true;
	cntFrame = 0;
	transform.Rotate(0.0f, 0.0f, RandomRangef(0.0f, 360.0f));
	transform.scale = RandomRangef(0.3f, 1.0f) * D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	speed = RandomRangef(BOMBERTRAIL_SPEED_MIN, BOMBERTRAIL_SPEED_MAX);
	lifeFrame = RandomRange(BOMBERTRAIL_LIFE_MIN, BOMBERTRAIL_LIFE_MAX);

	moveDir.x += RandomRangef(-0.1f, 0.1f);
	moveDir.y += RandomRangef(-0.1f, 0.1f);
}

/**************************************
PlayerBomberParticle�X�V����
***************************************/
void PlayerBomberParticle::Update()
{
	//�ړ�����
	transform.pos += moveDir * speed;

	//��������
	cntFrame++;

	float t = (float)cntFrame /(float)lifeFrame;

	if (cntFrame > lifeFrame)
	{
		active = false;
	}
}

/**************************************
PlayerBomberParticle�p�����[�^�ݒ�
***************************************/
void PlayerBomberParticle::SetMoveDir(const D3DXVECTOR3& moveDir)
{
	this->moveDir = moveDir;
}

/**************************************
PlayerBomberParticleEmitter����������
***************************************/
void PlayerBomberParticleEmitter::Init()
{
	prevPos = transform.pos;
	active = true;
	cntFrame = 0;
}

/**************************************
PlayerBomberParticleEmitter�I������
***************************************/
void PlayerBomberParticleEmitter::Uninit()
{
	parentActive = nullptr;
	parentPos = nullptr;
}

/**************************************
PlayerBomberParticleEmitter�X�V����
***************************************/
void PlayerBomberParticleEmitter::Update()
{
	prevPos = transform.pos;
	transform.pos = *parentPos;

	if (!*parentActive)
		active = false;
}

/**************************************
PlayerBomberParticleEmitter�p�����[�^�ݒ�
***************************************/
void PlayerBomberParticleEmitter::SetParameter(bool* pActive, D3DXVECTOR3 *pPos)
{
	this->parentActive = pActive;
	this->parentPos = pPos;
}


