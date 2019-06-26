//=====================================
//
//�v���C���[�g���C���p�[�e�B�N������[PlayerTrailParticle.cpp]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "PlayerTrailParticle.h"

/**************************************
�}�N����`
***************************************/

/**************************************
�\���̒�`
***************************************/

/**************************************
�O���[�o���ϐ�
***************************************/

/**************************************
PlayerTrailParticle����������
***************************************/
void PlayerTrailParticle::Init()
{
	const int LifeRange = 10;
	const int InitLife = 11;
	const float InitSpeed = 5.0f;
	const float SpeedRange = 3.0f;

	lifeFrame = InitLife + RandomRange(-LifeRange, LifeRange);
	cntFrame = 0;
	moveDir = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	speed = InitSpeed + RandomRangef(-SpeedRange, SpeedRange);
	active = true;
}

/**************************************
PlayerTrailParticle�I������
***************************************/
void PlayerTrailParticle::Uninit()
{
	active = false;
}

/**************************************
PlayerTrailParticle�X�V����
***************************************/
void PlayerTrailParticle::Update()
{
	cntFrame++;

	//�ړ�
	transform.pos += moveDir * speed;
	
	//��������
	if (cntFrame > lifeFrame)
	{
		active = false;
	}
}

/**************************************
PlayerTrailEmitter����������
***************************************/
void PlayerTrailEmitter::Init()
{
	active = true;
}

/**************************************
PlayerTrailEmitter�I������
***************************************/
void PlayerTrailEmitter::Uninit()
{
	parentPos = NULL;
	parentActive = NULL;
	active = false;
}

/**************************************
PlayerTrailEmitter�X�V����
***************************************/
void PlayerTrailEmitter::Update()
{
	if (*parentActive == false)
	{
		Uninit();
		return;
	}

	prevPos = transform.pos;
	transform.pos = *parentPos;
}

/**************************************
PlayerTrailEmitter�Z�b�g����
***************************************/
void PlayerTrailEmitter::SetParent(D3DXVECTOR3 *pPos, bool *pActive)
{
	parentPos = pPos;
	parentActive = pActive;
}
