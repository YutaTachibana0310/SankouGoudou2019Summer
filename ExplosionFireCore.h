//=====================================
//
//�G�N�X�v���[�W�����t�@�C�A�R�A�w�b�_[ExplosionFireCore.h]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _EXPLOSIONFIRECORE_H_
#define _EXPLOSIONFIRECORE_H_

#include "main.h"
#include "Framework\BaseParticle.h"
#include "Framework\BaseEmitter.h"
#include "Framework\BaseParticleController.h"

/**************************************
�O���錾
***************************************/

/**************************************
�}�N���E�񋓎q��`
***************************************/

/**************************************
ExplosionFireCore�N���X
***************************************/
class ExplosionFireCore : public BaseParticle
{
public:
	void Init();
	void Update();

	Transform *parent;
};

/**************************************
ExplosionFireCoreEmitter�N���X
***************************************/
class ExplosionFireCoreEmitter : public BaseEmitter
{
public:
	void Init();
	void Update();
};

/**************************************
ExplosionFireCoreController�N���X
***************************************/
class ExplosionFireCoreController : public BaseParticleController
{
public:
	void Init();
	void Emit();
	bool Draw();
};
#endif