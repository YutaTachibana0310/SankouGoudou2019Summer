//=====================================
//
//�v���C���[�`���[�W�G�t�F�N�g�w�b�_[PlayerChargeEffect.h]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _PLAYERCHARGEEFFECT_H_
#define _PLAYERCHARGEEFFECT_H_

#include "main.h"
#include "Framework\AnimationParticle.h"
#include "Framework\BaseEmitter.h"

/**************************************
�}�N����`
***************************************/

/**************************************
PlayerChargeEffect�N���X
***************************************/
class PlayerChargeEffect : public AnimationParticle
{
public:
	void Init();
	void Update();
};

/**************************************
PlayerChargeEffectEmitter�N���X
***************************************/
class PlayerChargeEffectEmitter : public BaseEmitter
{
public:
	void Init();
	void Update();
};

#endif