//=====================================
//
//GameOver.h
//�@�\:�Q�[���I�[�o�[�\��
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _GAMEOVER_H_
#define _GAMEOVER_H_

#include "main.h"
#include "Framework\Polygon2D.h"

/**************************************
�O���錾
***************************************/

/**************************************
�N���X��`
***************************************/
class GameOver : Polygon2D
{
public:
	GameOver();

	void Update();
	void Draw();
private:
	int cntFrame;

	const int Duration = 120;
};
#endif