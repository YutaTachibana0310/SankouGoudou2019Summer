//=====================================
//
//�G�l�~�[�o���b�g�`���[�W�R���g���[���w�b�_[EnemyBulletChargeController.h]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _ENEMYBULLETCHARGECONTROLLER_H_
#define _ENEMYBULLETCHARGECONTROLLER_H_

#include "main.h"
#include "Framework\BaseParticleController.h"

/**************************************
�}�N����`
***************************************/

/**************************************
�N���X��`
***************************************/
class EnemyBulletChargeController : public BaseParticleController
{
public:
	void Init();
	void Emit();
};

#endif