//=====================================
//
//�G�l�~�[�K�C�h�A���[�R���g���[���w�b�_[EnemyGuideArrowController.h]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _ENEMYGUIDEARROWCONTROLLER_H_
#define _ENEMYGUIDEARROWCONTROLLER_H_

#include "main.h"
#include "Framework\BaseParticleController.h"

class LineTrailModel;
/**************************************
�}�N����`
***************************************/

/**************************************
�N���X��`
***************************************/
class EnemyGuideArrowController : public BaseParticleController
{
public:
	void Init();
	void Emit();

	void SetEmitter(LineTrailModel* model);
};

#endif