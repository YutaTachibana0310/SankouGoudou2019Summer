//=====================================
//
//�v���C���[�{���o�[�p�[�e�B�N������[PlayerBomberParticle.cpp]
//Author:GP12B332 12 ����
//
//=====================================
#include "PlayerBomberParticle.h"
#include "Framework\Easing.h"

/**************************************
�}�N����`
***************************************/

/**************************************
PlayerBomber����������
***************************************/
void PlayerBomberParticle::Init()
{
	active = true;
	cntFrame = 0;
	transform.scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
}

/**************************************
PlayerBomber�I������
***************************************/
void PlayerBomberParticle::Uninit()
{
	active = false;
}

/**************************************
PlayerBomber�X�V����
***************************************/
void PlayerBomberParticle::Update()
{
	//�ړ�����
	transform.pos += moveDir * speed;
	transform.rot.z += 2.0f;
	transform.scale.x -= 0.01f;
	transform.scale.y -= 0.01f;

	//��������
	cntFrame++;
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
	//oldPos = *parentPos;
	transform.pos = *parentPos;

	//transform.pos - oldPos;

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


