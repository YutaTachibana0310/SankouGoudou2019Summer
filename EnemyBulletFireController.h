//=====================================
//
//�G�l�~�[�o���b�g�t�@�C�A�R���g���[���w�b�_[EnemyBulletFireController.h]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _ENEMYBULLETFIRECONTROLLER_H_
#define _ENEMYBULLETFIRECONTROLLER_H_

#include "main.h"
#include "Framework\BaseParticleController.h"

/**************************************
�}�N����`
***************************************/

/**************************************
�N���X��`
***************************************/
class EnemyBulletFireController : public BaseParticleController
{
public:
	void Init();
	void Emit();
};

#endif