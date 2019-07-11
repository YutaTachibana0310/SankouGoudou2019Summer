//=====================================
//
//�x�[�X�p�[�e�B�N���w�b�_[BaseParticle.h]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _BASEPARTICLE_H_
#define _BASEPARTICLE_H_

#include "../main.h"

/**************************************
�}�N����`
***************************************/

/**************************************
BaseParticle�N���X
���p�����Init(), Update()����������
***************************************/
class BaseParticle
{
public:
	BaseParticle();
	virtual ~BaseParticle();

	virtual void Init() = 0;
	virtual void Uninit();
	virtual void Update() = 0;
	void EmbedTransform(Transform *pTransform);
	bool active;

	Transform transform;
	ParticleUV uv;
	int lifeFrame;

protected:
	int cntFrame;
};

#endif