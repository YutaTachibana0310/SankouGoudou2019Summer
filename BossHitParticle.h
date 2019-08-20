//=====================================
//
//�{�X�q�b�g�p�[�e�B�N���w�b�_[BossHitParticle.h]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _BOSSHITPARTICLE_H_
#define _BOSSHITPARTICLE_H_

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
BossHitParticle�N���X
***************************************/
class BossHitParticle : public BaseParticle
{
public:
	BossHitParticle();

	void Init();
	void Update();

private:
	float speed;
	D3DXVECTOR3 moveDir;
};

/**************************************
BossHitParticleEmitter�N���X
***************************************/
class BossHitParticleEmitter : public BaseEmitter
{
	void Init();
	void Update();
};

/**************************************
BossHitParticleController�N���X
***************************************/
class BossHitParticleController : public BaseParticleController
{
	void Init();
	void Emit();
};

#endif