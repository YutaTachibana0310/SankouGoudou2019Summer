//=====================================
//
//TutorialScene.h
//�@�\:�`���[�g���A���V�[��
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _TUTORIALSCENE_H_
#define _TUTORIALSCENE_H_

#include "main.h"
#include "IStateScene.h"

/**************************************
�O���錾
***************************************/
class TutorialBG;

/**************************************
�N���X��`
***************************************/
class TutorialScene : public IStateScene
{
public:
	void Init() override;
	void Uninit() override;
	void Update(HWND hWnd) override;
	void Draw() override;

private:
	TutorialBG * bg;
};

#endif