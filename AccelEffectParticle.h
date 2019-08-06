//=====================================
//
//�A�N�Z���G�t�F�N�g�p�[�e�B�N���w�b�_[AccelEffectParticle.h]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _ACCELEFFECTPARTICLE_H_
#define _ACCELEFFECTPARTICLE_H_

#include "main.h"
#include "Framework\BaseParticle.h"
#include "Framework\BaseEmitter.h"

/**************************************
�}�N����`
***************************************/

/**************************************
AccelEffectParticle�N���X
***************************************/
class AccelEffectParticle : public BaseParticle
{
public:
	void Init();
	void Update();

private:
	D3DXVECTOR3 moveDir;
	D3DXVECTOR3 baseScale;
};

/**************************************
AccelEffectParticleEmitter�N���X
***************************************/
class AccelEffectParticleEmitter : public BaseEmitter
{
	void Init();
	void Update();
};

#endif