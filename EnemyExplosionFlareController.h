//=====================================
//
//�G�l�~�[�G�N�X�v���[�W�����t���A�R���g���[���w�b�_[EnemyExplosionFlareController.h]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _ENEMYEXPLOSIONFLARECONTROLLER_H_
#define _ENEMYEXPLOSIONFLARECONTROLLER_H_

#include "main.h"
#include "Framework\BaseParticleController.h"

/**************************************
�}�N����`
***************************************/

/**************************************
�N���X��`
***************************************/
class EnemyExplosionFlareController : public BaseParticleController
{
public:
	void Init();
	void Emit();
};

#endif