//=====================================
//
//�v���C���[�o���b�g�p�[�e�B�N���R���g���[���w�b�_[PlayerBulletParticleController.h]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _PLAYERBULLETPARTICLECONTROLLER_H_
#define _PLAYERBULLETPARTICLECONTROLLER_H_

#include "main.h"
#include "Framework\BaseParticleController.h"

/**************************************
�}�N����`
***************************************/

/**************************************
�N���X��`
***************************************/
class PlayerBulletParticleController : public BaseParticleController
{
public:
	void Init();
	void Emit();
	void SetEmitter(D3DXVECTOR3 *pPos, bool *pActive, D3DXVECTOR3 *edgeRight, D3DXVECTOR3 *edgeLeft);
};

#endif