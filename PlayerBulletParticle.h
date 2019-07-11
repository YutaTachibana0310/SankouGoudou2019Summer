#pragma once
//=====================================
//
//�v���C���[�o���b�g�p�[�e�B�N���w�b�_[PlayerBulletParticle.h]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _PLAYERBULLETPARTICLE_H_
#define _PLAYERBULLETPARTICLE_H_

#include "main.h"
#include "Framework\BaseParticle.h"
#include "Framework\BaseEmitter.h"

/**************************************
�}�N����`
***************************************/

/**************************************
PlayerBulletParticle�N���X��`
***************************************/
class PlayerBulletParticle : public BaseParticle
{
public:
	PlayerBulletParticle() {}
	~PlayerBulletParticle() {}

	void Init();
	void Uninit();
	void Update();
	void SetParameter(D3DXVECTOR3 *moveDir, int lifeFrame);

	D3DXVECTOR3 moveDir;
	float speed;
};

/**************************************
PlayerBulletParticleEmitter�N���X��`
***************************************/
class PlayerBulletParticleEmitter : public BaseEmitter
{
public:
	PlayerBulletParticleEmitter() : BaseEmitter() {}

	void Init();
	void Uninit();
	void Update();
	void SetParameter(bool* pActive, D3DXVECTOR3 *pPos, D3DXVECTOR3 *pEdgeRight, D3DXVECTOR3 *pEdgeLeft);

	bool *parentActive;
	D3DXVECTOR3 *parentPos;
	D3DXVECTOR3 edgeRight, edgeLeft;
};

#endif