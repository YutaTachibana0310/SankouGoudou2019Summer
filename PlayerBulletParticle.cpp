//=====================================
//
//�v���C���[�o���b�g�p�[�e�B�N������[PlayerBulletParticle.cpp]
//Author:GP12A332 21 ���ԗY��
//
//=====================================
#include "PlayerBulletParticle.h"
#include "Framework\Easing.h"

/**************************************
�}�N����`
***************************************/

/**************************************
PlayerBullet����������
***************************************/
void PlayerBulletParticle::Init()
{
	active = true;
	cntFrame = 0;
	transform.scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	transform.scale.x += fabsf(moveDir.x)* 10.0f;
	transform.scale.y += fabsf(moveDir.y)* 10.0f;
}

/**************************************
PlayerBullet�I������
***************************************/
void PlayerBulletParticle::Uninit()
{
	active = false;
}

/**************************************
PlayerBullet�X�V����
***************************************/
void PlayerBulletParticle::Update()
{
	//�ړ�����
	transform.pos += moveDir * speed;

	//��������
	cntFrame++;
	if (cntFrame > lifeFrame)
	{
		active = false;
	}
}

/**************************************
PlayerBulletParticle�p�����[�^�ݒ�
***************************************/
void PlayerBulletParticle::SetParameter(D3DXVECTOR3 *moveDir, int lifeFrame)
{
	this->moveDir = *moveDir;
	this->lifeFrame = lifeFrame;
}

/**************************************
PlayerBulletParticleEmitter����������
***************************************/
void PlayerBulletParticleEmitter::Init()
{
	active = true;
	cntFrame = 0;
}

/**************************************
PlayerBulletParticleEmitter�I������
***************************************/
void PlayerBulletParticleEmitter::Uninit()
{
	parentActive = nullptr;
	parentPos = nullptr;
}

/**************************************
PlayerBulletParticleEmitter�X�V����
***************************************/
void PlayerBulletParticleEmitter::Update()
{
	transform.pos = *parentPos;

	if (!*parentActive)
		active = false;
}

/**************************************
PlayerBulletParticleEmitter�p�����[�^�ݒ�
***************************************/
void PlayerBulletParticleEmitter::SetParameter(bool* pActive, D3DXVECTOR3 *pPos, D3DXVECTOR3 *pEdgeRight, D3DXVECTOR3 *pEdgeLeft)
{
	this->parentActive = pActive;
	this->parentPos = pPos;
	this->edgeLeft = *pEdgeLeft;
	this->edgeRight = *pEdgeRight;
}