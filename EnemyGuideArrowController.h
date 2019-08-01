//=====================================
//
//�G�l�~�[�K�C�h�A���[�R���g���[���w�b�_[EnemyGuideArrowController.h]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _ENEMYGUIDEARROWCONTROLLER_H_
#define _ENEMYGUIDEARROWCONTROLLER_H_

#include "main.h"
#include "EnemyGuideArrow.h"

#include <array>

class LineTrailModel;
/**************************************
�}�N����`
***************************************/
#define ENEMYGUIDEARROW_EMITTER_MAX		(10)

/**************************************
�N���X��`
***************************************/
class EnemyGuideArrowController
{
public:
	EnemyGuideArrowController();
	~EnemyGuideArrowController();

	void Update();
	void Draw();

	void SetEmitter(LineTrailModel model);

private:
	std::array<EnemyGuideArrowEmitter*, ENEMYGUIDEARROW_EMITTER_MAX> emitterContainer;
};

#endif