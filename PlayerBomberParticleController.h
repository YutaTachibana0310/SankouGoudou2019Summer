//=====================================
//
//�v���C���[�{���o�[�p�[�e�B�N���R���g���[���w�b�_[PlayerBomberParticleController.h]
//Author:GP12B332 12�@����
//
//=====================================
#ifndef _PLAYERBOMBERPARTICLECONTROLLER_H_
#define _PLAYERBOMBERPARTICLECONTROLLER_H_

#include "main.h"
#include "Framework/BaseParticleController.h"

/*******************************************
�}�N����`
********************************************/


/*******************************************
�N���X��`
********************************************/
class PlayerBomberParticleController : public BaseParticleController
{
public:
	void Init();
	void Emit();
	void SetEmitter(D3DXVECTOR3 *pPos, bool *pActive);

};

#endif



