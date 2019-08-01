//=============================================================================
//
// �^�C�g�����S��ʏ��� [titleLogoUI.h]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#ifndef _TITLELOGO_H_
#define _TITLELOGO_H_
#include "UIdrawer.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	ADRESS_TEXTURE_TITLELOGO	("data/TEXTURE/UI/�`�[�����S.png")	// �ǂݍ��ރe�N�X�`���t�@�C����

#include "TitleSceneUIManager.h"

class Object;

/**************************************
�O���錾
***************************************/
class TitleSceneUI;

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
class TitleLogo :public TitleSceneUI
{
public:
	Object *object;
	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
};

#endif

