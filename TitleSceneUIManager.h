//=============================================================================
//
// Title�V�[��UI�Ǘ����� [TitleSceneUIMaager.h]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#ifndef _TITLESCENEUIMANAGER_H_
#define _TITLESCENEUIMANAGER_H_

#include "UIdrawer.h"
#include "masktex.h"

/**************************************
�O���錾
***************************************/
class Object;
class TitleBG;
class Cursor;
class TitleLogo;
class StartButton;
class StartButtonManager;

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
class TitleSceneUI
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

class StartButtonManager
{
public:
	StartButtonManager *startButtonManager;

	void GoGameScene()
	{
		SceneChangeFlag(true, SceneGame);
	}
};

#endif


