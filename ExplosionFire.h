//=====================================
//
//�G�N�X�v���[�W�����t�@�C�A�w�b�_[ExplosionFire.h]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _EXPLOSIONFIRE_H_
#define _EXPLOSIONFIRE_H_

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
ExplosionFire�N���X
***************************************/
class ExplosionFire : public AnimationParticle
{
public:
	ExplosionFire();
	void Init();
	void Update();

private:
	float speed;
	D3DXVECTOR3 moveDir;
};

/**************************************
ExplosionFireEmitter�N���X
***************************************/
class ExplosionFireEmitter : public BaseEmitter
{
public:
	void Init();
	void Update();
};

/**************************************
ExplosionFireController�N���X
***************************************/
class ExplosionFireController : public BaseParticleController
{
public:
	void Init();
	void Emit();
};

#endif