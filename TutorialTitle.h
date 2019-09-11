//=====================================
//
//TutorialTitle.h
//�@�\:
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _TUTORIALTITLE_H_
#define _TUTORIALTITLE_H_

#include "main.h"
#include "Framework\Polygon2D.h"

/**************************************
�O���錾
***************************************/

/**************************************
�N���X��`
***************************************/
class TutorialTitle : public Polygon2D
{
public:
	TutorialTitle();

	void Update();

	static const int FadeInDuration;
	static const int ViewDuration;
	static const int MoveDuration;
	static const int FadeOutDuration;

private:
	int cntFrame;
};
#endif