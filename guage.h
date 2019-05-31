//=============================================================================
//
// �Q�[�W��ʏ��� [guage.h]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#ifndef _GUAGE_H_
#define _GUAGE_H_

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	ADRESS_TEXTURE_GUAGEBAR	("data/TEXTURE/UI/guageBar.png")		
#define	ADRESS_TEXTURE_GUAGEFLAME ("data/TEXTURE/UI/guageFlame.png")		

enum GUARGE_PARTS
{
	GUAGEBAR_DAMAGE,  // �_���[�W�\���Q�[�W�o�[
	GUAGEBAR_TRUE,	  // ���ۂ̃Q�[�W�o�[
	GUAGEFLAME,
};

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitGuageParts(void);
void UninitGuageParts(void);
void UpdateGuageParts(void);
void DrawGuageParts(void);
void ChangeGuage(float value);

#endif

