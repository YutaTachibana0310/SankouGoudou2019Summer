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
#define BOMBER_PARTICLE_ROT	(2.0f)

/**************************************
PlayerBomberParticle����������
***************************************/
void PlayerBomberParticle::Init()
{
	active = true;
	cntFrame = 0;
	transform.scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
}

/**************************************
PlayerBomberParticle�I������
***************************************/
void PlayerBomberParticle::Uninit()
{
	active = false;
}

/**************************************
PlayerBomberParticle�X�V����
***************************************/
void PlayerBomberParticle::Update()
{
	//�ړ�����
	transform.pos += moveDir * speed;
	transform.rot.z += BOMBER_PARTICLE_ROT;
	//transform.scale.x -= 0.01f;
	//transform.scale.y -= 0.01f;

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
void PlayerBomberParticle::SetParameter(D3DXVECTOR3 *moveDir, int lifeFrame)
{
	this->moveDir = *moveDir;
	this->lifeFrame = lifeFrame;
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


