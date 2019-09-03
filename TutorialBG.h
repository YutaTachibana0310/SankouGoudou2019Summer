//=====================================
//
//TutorialBG.h
//�@�\:�`���[�g���A���V�[���̔w�i
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _TUTORIALBG_H_
#define _TUTORIALBG_H_

#include "main.h"
#include "SkyBox.h"

/**************************************
�O���錾
***************************************/
class Polygon2D;

/**************************************
�N���X��`
***************************************/
class TutorialBG : public SkyBox
{
public:
	TutorialBG();

	void Draw();
	void Update();

private:
	Polygon2D *polygon;

	static const D3DXVECTOR3 BoxSize;
	static const D3DXVECTOR2 BoxUV;
	static const float ScrollSpeed;
};

#endif