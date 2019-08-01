//=============================================================================
//
// スタートボタン画面処理 [startButtonUI.h]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#ifndef _STARTBUTTON_H_
#define _STARTBUTTON_H_

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	ADRESS_TEXTURE_STARTBUTTON_BG	("data/TEXTURE/UI/startButtonBG.png")	// 読み込むテクスチャファイル名
#define	ADRESS_TEXTURE_STARTBUTTON_TEXT	("data/TEXTURE/UI/startButtonText.png")	// 読み込むテクスチャファイル名

#include "TitleSceneUIManager.h"

enum STARTBUTTON_PARTS
{
	BACKGROUND_STARTBUTTON,
	TEXT_STARTBUTTON,
};
#include "UIdrawer.h"

class Object;

/**************************************
前方宣言
***************************************/
class TitleSceneUI;

//*****************************************************************************
// 構造体定義
//*****************************************************************************
class StartButton :public TitleSceneUI
{
public:
	Object *object;
	void Init(void);
	void Uninit(void);
	void Update(HWND hWnd);
	void Draw(void);

private:
	void BlinkStartButtonText(void);
	bool IsMouseOvered(HWND hWnd, D3DXVECTOR3 pos, D3DXVECTOR3 size);
};

#endif

