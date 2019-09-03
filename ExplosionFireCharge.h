//=====================================
//
//�G�N�X�v���[�W�����t�@�C�A�`���[�W�w�b�_[ExplosionFireCharge.h]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _EXPLOSIONFIRECHARGE_H_
#define _EXPLOSIONFIRECHARGE_H_

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
ExplisionFireCharge�N���X
***************************************/
class ExplosionFireCharge : public BaseParticle
{
public:
	ExplosionFireCharge();
	void Init();
	void Update();

	Transform *parent;

private:
	D3DXVECTOR3 offset;
};

/**************************************
ExplisionFireChageEmitter�N���X
***************************************/
class ExplosionFireChargeEmitter : public BaseEmitter
{
public:
	void Init();
	void Update();
};

/**************************************
ExplisionFireChargeController�N���X
***************************************/
class ExplosionFireChargeController : public BaseParticleController
{
public:
	void Init();
	void Emit();
	bool Draw();
};

#endif