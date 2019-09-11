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
#include <vector>

/**************************************
�O���錾
***************************************/

/**************************************
�N���X��`
***************************************/
class TutorialGuide : public Polygon2D
{
public:
	//�`���[�g���A���̃X�e�b�v��`
	enum TutorialStep
	{
		MoveButton,
		ComboReset,
		BombStock,
		FireBomber,
		TutorialEnd,
		Max
	};

	TutorialGuide();

	void Update();
	void Draw();

	bool Set(int step);

	static const int FadeDuration;
	static const int LifeFrame;
	
private:
	int cntFrame;
	std::vector<LPDIRECT3DTEXTURE9> textureContainer;
};

#endif