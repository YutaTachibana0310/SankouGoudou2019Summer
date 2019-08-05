//=============================================================================
//
// �e���b�v�w�i���� [telopBG.h]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#ifndef _TELOP_BG_H_
#define _TELOP_BG_H_

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	ADRESS_TEXTURE_TELOP_BG	("data/TEXTURE/UI/telop/telopBG.png")	// �ǂݍ��ރe�N�X�`���t�@�C����

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitTelopBG(void);
void UninitTelopBG(void);
void UpdateTelopBG(void);
void DrawTelopBG(void);

void AvctivateTelopBGOpen(void);
void AvctivateTelopBGClose(void);

bool GetTelopBGOpenActive(void);
bool GetTelopBGCloseActive(void);

#endif
