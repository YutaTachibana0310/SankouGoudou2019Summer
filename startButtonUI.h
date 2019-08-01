//=============================================================================
//
// �X�^�[�g�{�^����ʏ��� [startButtonUI.h]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#ifndef _STARTBUTTON_H_
#define _STARTBUTTON_H_

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	ADRESS_TEXTURE_STARTBUTTON_BG	("data/TEXTURE/UI/startButtonBG.png")	// �ǂݍ��ރe�N�X�`���t�@�C����
#define	ADRESS_TEXTURE_STARTBUTTON_TEXT	("data/TEXTURE/UI/startButtonText.png")	// �ǂݍ��ރe�N�X�`���t�@�C����

#include "TitleSceneUIManager.h"

enum STARTBUTTON_PARTS
{
	BACKGROUND_STARTBUTTON,
	TEXT_STARTBUTTON,
};
#include "UIdrawer.h"

class Object;

/**************************************
�O���錾
***************************************/
class TitleSceneUI;

//*****************************************************************************
// �\���̒�`
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

