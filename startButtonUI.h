//=============================================================================
//
// スタートボタン画面処理 [startButtonUI.h]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#ifndef _STARTBUTTON_H_
#define _STARTBUTTON_H_

/**************************************
前方宣言
***************************************/
class Object;
class Mask;

//*****************************************************************************
// 構造体定義
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

