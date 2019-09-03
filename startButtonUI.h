//=============================================================================
//
// �X�^�[�g�{�^����ʏ��� [startButtonUI.h]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#ifndef _STARTBUTTON_H_
#define _STARTBUTTON_H_

/**************************************
�O���錾
***************************************/
class Object;
class Mask;

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
class StartButton
{
public:
	StartButton();
	~StartButton();
	void Update(HWND hWnd);
	void Draw(void);

private:
	Object *bg;
	Object *text;
	Mask *mask;
	void GoGameScene(void);
	void BlinkStartButtonText(void);
};

#endif

