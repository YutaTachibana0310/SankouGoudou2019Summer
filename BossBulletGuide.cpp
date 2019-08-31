//=====================================
//
//�{�X�o���b�g�K�C�h����[BossBulletGuide.cpp]
//Author:GP12A332 21 ���ԗY��
//
//=====================================
#include "BossBulletGuide.h"

/**************************************
�O���[�o���ϐ�
***************************************/

/**************************************
�R���X�g���N�^
***************************************/
BossBulletGuide::BossBulletGuide() :
	Polygon2D(50.0f, 50.0f),
	cntFrame(0),
	Duration(60)
{
	LoadTexture("data/TEXTURE/UI/Boss/bulletGuide.png");
}

/**************************************
�X�V����
***************************************/
void BossBulletGuide::Update()
{
	if (cntFrame > Duration)
		return;

	cntFrame++;
}

/**************************************
�Z�b�g����
***************************************/
void BossBulletGuide::Set(const D3DXVECTOR3 & pos)
{
	transform.pos = pos;
	cntFrame = 0;
}

/**************************************
�A�N�e�B�u����
***************************************/
bool BossBulletGuide::IsActive()
{
	return cntFrame <= Duration;
}
