//=====================================
//
//�A�j���[�V�����p�[�e�B�N���w�b�_[AnimationParticle.h]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _ANIMATIONPARTICLE_H_
#define _ANIMATIONPARTICLE_H_

#include "../main.h"
#include "BaseParticle.h"

/**************************************
�}�N����`
***************************************/

/**************************************
AnimationParticle�N���X
***************************************/
class AnimationParticle : public BaseParticle
{
public:
	void SetAnimParameter(float texDixX, float texDivY);
	void SetAnimParameter(D3DXVECTOR2* texDiv);

protected:
	void Animation(float t);

	int animIndexMax;
	D3DXVECTOR2 texDiv;
	D3DXVECTOR2 texSize;
};
#endif