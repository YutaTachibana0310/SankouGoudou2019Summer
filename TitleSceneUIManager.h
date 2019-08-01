//=============================================================================
//
// Title�V�[��UI�Ǘ����� [TitleSceneUIMaager.h]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#ifndef _TITLESCENEUIMANAGER_H_
#define _TITLESCENEUIMANAGER_H_

#include "UIdrawer.h"

/**************************************
�O���錾
***************************************/
class Object;
class TitleBG;
class Cursor;
class TitleLogo;
class StartButton;

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
class TitleSceneUI:public Object
{
public:
	TitleBG*titleBG;
	Cursor*cursor;
	TitleLogo*titleLogo;
	StartButton*startButton;

	void Init(void);
	void Uninit(void);
	void Update(HWND hWnd);
	void Draw(void);

};

#endif


