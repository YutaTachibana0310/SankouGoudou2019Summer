//=============================================================================
//
// �^�C�g���w�i��ʏ��� [titleBGUI.h]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#ifndef _TITLEBG_H_
#define _TITLEBG_H_
#include "UIdrawer.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	ADRESS_TEXTURE_TITLEBG	("data/TEXTURE/UI/title_test.jpg")	// �ǂݍ��ރe�N�X�`���t�@�C����

#include "TitleSceneUIManager.h"
#include "UIdrawer.h"

class Object;

/**************************************
�O���錾
***************************************/
class TitleSceneUI;

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
class TitleBG :public TitleSceneUI
{
public:
	Object *object;
	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
};

#endif