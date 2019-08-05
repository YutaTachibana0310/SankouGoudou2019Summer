//=====================================
//
//�v���C���[�`���[�W�p�[�e�B�N���w�b�_[PlayerChargeParticle.h]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _PLAYERCHARGEPARTICLE_H_
#define _PLAYERCHARGEPARTICLE_H_

#include "main.h"
#include "Framework\BaseParticle.h"
#include "Framework\BaseEmitter.h"

/**************************************
�}�N����`
***************************************/

/**************************************
PlayerChargeParticle�N���X
***************************************/
class PlayerChargeParticle : public BaseParticle
{
public:
	void Init();
	void Update();

private:
	D3DXVECTOR3 moveDir;
	float speed;
};

/**************************************
PlayerChargeParticleEmitter�N���X
***************************************/
class PlayerChargeParticleEmitter : public BaseEmitter
{
public:
	void Init();
	void Update();
};

#endif