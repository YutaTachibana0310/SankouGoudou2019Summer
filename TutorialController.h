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
	std::vector<TutorialGuide*> tutorialContainer;

	const int StepMax = 1;
};

#endif