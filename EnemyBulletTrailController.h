//=====================================
//
//�G�l�~�[�o���b�g�g���C���R���g���[���w�b�_[EnemyBulletTrailController.h]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _ENEMYBULLETTRAILCONTROLLER_H_
#define _ENEMYBULLETTRAILCONTROLLER_H_

#include "main.h"
#include "Framework\BaseParticleController.h"

/**************************************
�}�N����`
***************************************/

/**************************************
�N���X��`
***************************************/
class EnemyBulletTrailController : public BaseParticleController
{
public:
	void Init();
	void Emit();
};

#endif