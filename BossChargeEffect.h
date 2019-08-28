//=====================================
//
//�{�X�`���[�W�G�t�F�N�g�@�w�b�_[BossChargeEffect.h]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _BOSSCHARGEFFECT_H_
#define _BOSSCHARGEFFECT_H_

#include "main.h"
#include "Framework\AnimationParticle.h"
#include "Framework\BaseEmitter.h"
#include "Framework\BaseParticleController.h"

/**************************************
�O���錾
***************************************/

/**************************************
�}�N���E�񋓎q��`
***************************************/

/**************************************
BossChargeParticle�N���X
***************************************/
class BossChargeParticle : public AnimationParticle
{
public:
	BossChargeParticle();

	void Init();
	void Update();
};

/**************************************
BossChargeEmitter�N���X
***************************************/
class BossChargeEmitter : public BaseEmitter
{
public:
	void Init();
	void Update();
};

/**************************************
BossChargeParticleController�N���X
***************************************/
class BossChargeParticleController : public BaseParticleController
{
public:
	void Init();
	void Emit();
};

#endif