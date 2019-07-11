//=====================================
//
//�A�j���[�V�����p�[�e�B�N������[AnimationParticle.cpp]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "AnimationParticle.h"

/**************************************
�}�N����`
***************************************/

/**************************************
�A�j���[�V��������
***************************************/
void AnimationParticle::Animation(float t)
{
	int animIndex = (int)(t * animIndexMax);

	int x = animIndex % (int)texDiv.x;
	int y = animIndex / (int)texDiv.x;

	uv.u = x * texSize.x;
	uv.v = y * texSize.y;
}

/**************************************
�A�j���[�V�����p�����[�^�Z�b�g����
***************************************/
void AnimationParticle::SetAnimParameter(float divX, float divY)
{
	texDiv = D3DXVECTOR2(divX, divY);
	texSize.x = 1.0f / divX;
	texSize.y = 1.0f / divY;

	animIndexMax = (int)(divX * divY) - 1;
}

/**************************************
�A�j���[�V�����p�����[�^�Z�b�g����
***************************************/
void AnimationParticle::SetAnimParameter(D3DXVECTOR2* texDiv)
{
	this->texDiv = *texDiv;
	texSize.x = 1.0f / texDiv->x;
	texSize.y = 1.0f / texDiv->y;

	animIndexMax = (int)(texDiv->x * texDiv->y) - 1;
}