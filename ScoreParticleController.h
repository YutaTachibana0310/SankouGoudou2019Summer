//=====================================
//
//�X�R�A�p�[�e�B�N���R���g���[���w�b�_[ScoreParticleController.h]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _SCOREPARTICLECONTROLLER_H_
#define _SCOREPARTICLECONTROLLER_H_

#include "main.h"
#include <vector>

#include "Framework\BaseParticleController.h"
#include "ScoreParticle.h"

/**************************************
�}�N����`
***************************************/

/**************************************
�O���錾
***************************************/
class ScoreParticle;
class ScoreParticleEmitter;

/**************************************
�N���X��`
***************************************/
class ScoreParticleController : public BaseParticleController
{
public:
	void Init();
	void SetEmitter(D3DXVECTOR3 *pos);
	void Emit();
};
#endif