//=============================================================================
//
// �X�e�[�W�N���A�e���b�v���� [stageClearTelop.h]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#ifndef _STAGE_CLEAR_TELOP_H_
#define _STAGE_CLEAR_TELOP_H_

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	ADRESS_TEXTURE_STAGE_CLEAR_TELOP	("data/TEXTURE/UI/telop/stageClearTelop.png")	// �ǂݍ��ރe�N�X�`���t�@�C����

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitStageClearTelop(void);
void UninitStageClearTelop(void);
void UpdateStageClearTelop(void);
void DrawStageClearTelop(void);

//�e���b�v�Z�b�g�֐�
void SetStageClearTelop(void);

#endif
