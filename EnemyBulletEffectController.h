//=====================================
//
//�G�l�~�[�o���b�g�G�t�F�N�g�R���g���[���w�b�_[EnemyBulletEffectController.h]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _ENEMYBULLETEFFECTCONTROLLER_H_
#define _ENEMYBULLETEFFECTCONTROLLER_H_

#include "main.h"
#include "Framework\BaseParticleController.h"
#include "LineTrailModel.h"

/**************************************
�}�N����`
***************************************/

/**************************************
�N���X��`
***************************************/
class EnemyBulletEffectController : public BaseParticleController
{
public:
	void Init();
	void Emit();
	BaseEmitter* SetEmitter(LineTrailModel model);
};

#endif