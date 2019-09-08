//=====================================
//
// TutorialGuide.h
// �@�\:�`���[�g���A���K�C�h
// Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _TUTORIALGUIDE_H_
#define _TUTORIALGUIDE_H_

#include "main.h"
#include "Framework\Polygon2D.h"

/**************************************
�O���錾
***************************************/

/**************************************
�N���X��`
***************************************/
class TutorialGuide : public Polygon2D
{
public:
	TutorialGuide(const char* TexturePath);

	void Update();

	static const int FadeDuration;
	static const int LifeFrame;

private:
	int cntFrame;
};

#endif