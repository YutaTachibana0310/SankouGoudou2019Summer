//=====================================
//
//�v���C���[�g���C���p�[�e�B�N���R���g���[���w�b�_[PlayerTrailParticleController.h]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _PLAYERTRAILPARTICLECONTROLLER_H_
#define _PLAYERTRAILPARTICLECONTROLLER_H_

#include "main.h"
#include "Framework\BaseParticleController.h"

/**************************************
�}�N����`
***************************************/

/**************************************
�N���X��`
***************************************/
class PlayerTrailParticleController : public BaseParticleController
{
public:
	void Init();
	void Emit();
	void SetEmitter(D3DXVECTOR3 *pPos, bool *pActive);
};

#endif