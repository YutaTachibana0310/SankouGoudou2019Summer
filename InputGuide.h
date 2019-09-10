//=====================================
//
//InputGuide.h
//�@�\:���̓K�C�h�\��
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _INPUTGUIDE_H_
#define _INPUTGUIDE_H_

#include "main.h"
#include "Framework\Polygon2D.h"

/**************************************
�O���錾
***************************************/
class LineTrailModel;

/**************************************
�N���X��`
***************************************/
class InputGuide : public Polygon2D
{
public:
	InputGuide();

	void Draw();
	void Set(LineTrailModel& model);

private:
	bool active;

};

#endif