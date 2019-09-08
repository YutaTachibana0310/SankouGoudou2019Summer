//=============================================================================
//
// Title�V�[��UI�Ǘ����� [TitleSceneUIMaager.h]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#ifndef _TITLESCENEUIMANAGER_H_
#define _TITLESCENEUIMANAGER_H_

#include "masktex.h"

namespace Title
{
	class Logo;
	class CityBG;
}

/**************************************
�O���錾
***************************************/
class TitleBG;
class TitleLogo;
class StartButton;
class StartButtonManager;
class Cursor;

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
class TitleSceneUIManager
{
public:
	TitleSceneUIManager();
	~TitleSceneUIManager();

	TitleBG *titleBG;
	TitleLogo *titleLogo;
	StartButton *startButton;

	//0907���Ԓǉ�
	Title::Logo *logo;
	Title::CityBG *bg;
	
	//0908���Ԓǉ�
	Cursor *cursor;

	void Init(void);
	void Uninit(void);
	void Update(HWND hWnd);
	void Draw(void);
};

#endif


