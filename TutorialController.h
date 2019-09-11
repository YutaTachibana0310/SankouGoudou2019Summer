//=====================================
//
// TutorialController.h
// �@�\:�`���[�g���A���Ǘ�����
// Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _TUTORIALCONTROLLER_H_
#define _TUTORIALCONTROLLER_H_

#include "main.h"
#include <vector>

/**************************************
�O���錾
***************************************/
class TutorialGuide;
class Polygon2D;
class TutorialTitle;

/**************************************
�N���X��`
***************************************/
class TutorialController
{
public:
	TutorialController();
	~TutorialController();

	void Update();
	void Draw();

private:
	int cntFrame;
	int step;
	bool isFinishTitle;

	TutorialGuide *guide;
	Polygon2D *skip;
	TutorialTitle *title;

	const int GuideDuration = 360;
};

#endif