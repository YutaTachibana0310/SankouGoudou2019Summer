//=====================================
//
//�G�l�~�[�G�N�X�v���[�W�����R���g���[���w�b�_[EnemyExplosionController.h]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _ENEMYEXPLOSIONCONTROLLER_H_
#define _ENEMYEXPLOSIONCONTROLLER_H_

#include "main.h"
#include "Framework\BaseParticleController.h"

/**************************************
�}�N����`
***************************************/

/**************************************
�N���X��`
***************************************/
class EnemyExplosionController : public BaseParticleController
{
public:
	void Init();
	void Emit();
};

#endif